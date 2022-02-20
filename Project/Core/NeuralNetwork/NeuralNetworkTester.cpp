#include "Core/NeuralNetwork/NeuralNetworkTester.h"
#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Shared/Communicator/Communicator.h"

#include <optional>

// test
#include "IrisDataExtractor.h"
#include <iostream>
// test

namespace Core {
namespace NodeNetwork {

const unsigned char NeuralNetworkTester::kPollCount = 10;

void NeuralNetworkTester::irisTest(
    const std::optional<unsigned long> &dataSeed,
    const unsigned long learningIterations,
    const unsigned long testingIterations, const QUuid &networkId,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork, const bool debug) {
  // setup test
  std::srand(dataSeed.has_value() ? dataSeed.value() : ulong(std::time(0)));

  std::vector<std::pair<std::vector<double>, std::vector<double>>> learningSet;
  std::vector<std::pair<std::vector<double>, std::vector<double>>> testingSet;
  learningSet.reserve(std::round(150 * 0.75));
  testingSet.reserve(std::round(150 * 0.75));

  Core::DataExtractor::DataExtractor::generateLearningAndTestingSets(
      learningSet, testingSet);

  test(learningSet, testingSet, learningIterations, testingIterations,
       networkId, neuralNetwork, debug);
}

void NeuralNetworkTester::test(
    const std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &learningSet,
    const std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &testingSet,
    const unsigned long learningIterations,
    const unsigned long testingIterations, const QUuid &networkId,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
    const bool debug = true) {

  unsigned long long poll = (learningIterations) / kPollCount;
  if (poll < 1) {
    poll = 1;
  }

  unsigned long correctCount = 0;
  std::vector<double> preLearningSetAccuracies;
  bool learn = false;
  {
    for (unsigned long i = 0; i < testingIterations; ++i) {
      std::pair<std::vector<double>, std::vector<double>> datapoint;
      datapoint.first.reserve(4);
      datapoint.second.reserve(3);
      Core::DataExtractor::DataExtractor::getRandomDatapoint(testingSet,
                                                             datapoint);
      const auto &[inputs, desiredOutputs] = datapoint;
      Q_ASSERT_X(
          datapoint.second.size() == 3, Q_FUNC_INFO,
          QString("Desired count: %1").arg(desiredOutputs.size()).toLatin1());

      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, learn);
      if (correct) {
        ++correctCount;
      }
    }
    double accuracy = 100.0 * correctCount / testingIterations;
    preLearningSetAccuracies.push_back(accuracy);
  }
  {
    if (debug) {
      std::cout << "accuracy before learning:\n";
      for (auto accuracy : preLearningSetAccuracies) {
        std::cout << accuracy << ", ";
      }
      std::cout << "\n\n";
    }
  }

  correctCount = 0;
  std::vector<double> learningSetAccuracies;
  learn = true;
  {
    auto &communicator = Shared::Communicator::Communicator::instance();

    for (unsigned long i = 0; i < learningIterations; ++i) {
      std::pair<std::vector<double>, std::vector<double>> datapoint{};
      datapoint.first.reserve(4);
      datapoint.second.reserve(3);
      Core::DataExtractor::DataExtractor::getRandomDatapoint(learningSet,
                                                             datapoint);
      auto &[inputs, desiredOutputs] = datapoint;
      Q_ASSERT_X(
          datapoint.second.size() == 3, Q_FUNC_INFO,
          QString("Desired count: %1").arg(desiredOutputs.size()).toLatin1());

      if (i != 0 && poll != 0 && i % poll == 0) {
        double accuracy = 100.0 * correctCount / poll;
        learningSetAccuracies.push_back(accuracy);
        correctCount = 0;

        bool correct =
            testIteration(inputs, desiredOutputs, neuralNetwork, learn);
        if (correct) {
          ++correctCount;
        }

        const auto dataAfter = neuralNetwork.getData();
        communicator.postEvent(
            new Shared::Communicator::EvNeuralNetRunInfo(networkId, dataAfter));
      } else {
        bool correct =
            testIteration(inputs, desiredOutputs, neuralNetwork, learn);
        if (correct) {
          ++correctCount;
        }

        if (i == 0) {
          const auto initialData = neuralNetwork.getData();
          communicator.postEvent(new Shared::Communicator::EvNeuralNetRunInfo(
              networkId, initialData));
        }
      }
    }
  }
  {
    if (debug) {
      std::cout << "accuracy while learning:\n";
      for (auto accuracy : learningSetAccuracies) {
        std::cout << accuracy << ", ";
      }
      std::cout << "\n\n";
    }
  }

  correctCount = 0;
  std::vector<double> testingSetAccuracies;
  learn = false;
  {
    for (unsigned long i = 0; i < testingIterations; ++i) {
      std::pair<std::vector<double>, std::vector<double>> datapoint;
      datapoint.first.reserve(4);
      datapoint.second.reserve(3);
      Core::DataExtractor::DataExtractor::getRandomDatapoint(testingSet,
                                                             datapoint);
      auto &[inputs, desiredOutputs] = datapoint;
      Q_ASSERT_X(
          datapoint.second.size() == 3, Q_FUNC_INFO,
          QString("Desired count: %1").arg(desiredOutputs.size()).toLatin1());

      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, learn);
      if (correct) {
        ++correctCount;
      }
    }
    double accuracy = 100.0 * correctCount / testingIterations;
    testingSetAccuracies.push_back(accuracy);
  }
  {
    if (debug) {
      std::cout << "accuracy after learning:\n";
      for (auto accuracy : testingSetAccuracies) {
        std::cout << accuracy << ", ";
      }
      std::cout << "\n\n";
    }
  }

  if (debug) {
    std::cout << "=================================\n";
  }
}

bool NeuralNetworkTester::testIteration(
    const std::vector<double> &inputValues,
    const std::vector<double> &desiredOutputs,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork, const bool learn) {
  // activate
  neuralNetwork.activate(inputValues);

  // compare to desired outputs
  std::vector<double> obtainedValues = neuralNetwork.outputValues();
  Q_ASSERT_X(obtainedValues.size() == desiredOutputs.size(), Q_FUNC_INFO,
             QString("Obtained count: %1\n Desired count: %2")
                 .arg(obtainedValues.size())
                 .arg(desiredOutputs.size())
                 .toLatin1());

  bool pass = !obtainedValues.empty();
  for (unsigned long obtainedValIdx = 0; obtainedValIdx < obtainedValues.size();
       ++obtainedValIdx) {
    if (std::round(obtainedValues[obtainedValIdx]) !=
        std::round(desiredOutputs[obtainedValIdx])) {
      pass = false;
      break;
    }
  }

  // teach the network
  if (learn) {
    neuralNetwork.backPropagete(desiredOutputs);
  }

  return pass;
}

} // namespace NodeNetwork
} // namespace Core
