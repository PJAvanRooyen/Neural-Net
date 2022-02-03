#include "NeuralNetworkManager.h"
#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkFactory.h"
#include "Shared/Communicator/Communicator.h"

// test
#include "../Tests/Core/NeuralNet/NeuralNetTest.h"
// test

namespace Core {
namespace NodeNetwork {

NeuralNetworkManager::NeuralNetworkManager(QObject *parent)
    : NodeNetworkManager(parent) {
  auto &communicator = Shared::Communicator::Communicator::instance();
  communicator.connect(this,
                       {Shared::Communicator::EvNeuralNetCreate::staticType(),
                        Shared::Communicator::EvNeuralNetRun::staticType()});
}

NeuralNetworkManager::~NeuralNetworkManager() {}

NeuralNetwork<double> *NeuralNetworkManager::createMeshNetwork(
    const std::vector<unsigned long> &layerSizes, const double learningRate,
    const std::optional<unsigned> seed, const QUuid &networkId) {

  auto *neuralNetwork = NeuralNetworkFactory::createMeshNetwork<double>(
      layerSizes, learningRate, seed);

  addNetwork(networkId, neuralNetwork);

  return neuralNetwork;
}

void NeuralNetworkManager::customEvent(QEvent *event) {
  const auto type = event->type();

  if (type == Shared::Communicator::EvNeuralNetCreate::staticType()) {
    auto *ev = static_cast<Shared::Communicator::EvNeuralNetCreate *>(event);

    auto *netualNet = createMeshNetwork(ev->layerSizes, ev->learningRate,
                                        ev->seed, ev->networkId);

    if (!netualNet) {
      return;
    }

    auto &communicator = Shared::Communicator::Communicator::instance();
    communicator.postEvent(
        new Shared::Communicator::EvNeuralNetCreateResponse(ev->networkId));

  } else if (type == Shared::Communicator::EvNeuralNetRun::staticType()) {
    auto *ev = static_cast<Shared::Communicator::EvNeuralNetRun *>(event);

    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        learningSet;
    std::vector<std::pair<std::vector<double>, std::vector<double>>> testingSet;

    Tests::NeuralNetTest::irisDataToNetworkInputs(
        learningSet, testingSet, 5, ev->learningIterations,
        ev->testingIterations, ev->dataSeed);

    test(learningSet, testingSet, network<NeuralNetwork<double>>(ev->networkId),
         100, true);
  }
}

void NeuralNetworkManager::test(
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>>
        learningSet,
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>>
        testingSet,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
    const double valuePollingRate, const bool debug) {

  const unsigned long long poll =
      (learningSet.size() + testingSet.size()) / valuePollingRate;

  unsigned long correctCount = 0;
  std::vector<double> preTestingSetAccuracies;
  std::vector<double> learningSetAccuracies;
  std::vector<double> testingSetAccuracies;

  correctCount = 0;

  for (unsigned long i = 0; i < testingSet.size(); ++i) {
    std::vector<double> inputs = testingSet[i].first;
    std::vector<double> desiredOutputs = testingSet[i].second;

    if (i != 0 && i % poll == 0) {
      double accuracy = 100.0 * correctCount / poll;
      preTestingSetAccuracies.push_back(accuracy);
      correctCount = 0;
      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, false, true);
      if (correct) {
        ++correctCount;
      }
    } else {
      // teach the network
      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, false, false);
      if (correct) {
        ++correctCount;
      }
    }
  }

  for (unsigned long i = 0; i < learningSet.size(); ++i) {
    std::vector<double> inputs = learningSet[i].first;
    std::vector<double> desiredOutputs = learningSet[i].second;

    if (i != 0 && poll != 0 && i % poll == 0) {
      double accuracy = 100.0 * correctCount / poll;
      learningSetAccuracies.push_back(accuracy);
      correctCount = 0;
      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, true, true);
      if (correct) {
        ++correctCount;
      }
    } else {
      // teach the network
      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, true, false);
      if (correct) {
        ++correctCount;
      }
    }
  }

  correctCount = 0;

  for (unsigned long i = 0; i < testingSet.size(); ++i) {
    std::vector<double> inputs = testingSet[i].first;
    std::vector<double> desiredOutputs = testingSet[i].second;

    if (i != 0 && i % poll == 0) {
      double accuracy = 100.0 * correctCount / poll;
      testingSetAccuracies.push_back(accuracy);
      correctCount = 0;
      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, false, true);
      if (correct) {
        ++correctCount;
      }
    } else {
      // teach the network
      bool correct =
          testIteration(inputs, desiredOutputs, neuralNetwork, false, false);
      if (correct) {
        ++correctCount;
      }
    }
  }

  if (debug) {
    std::cout << "accuracy before learning:\n";
    for (auto accuracy : preTestingSetAccuracies) {
      std::cout << accuracy << ", ";
    }
    std::cout << "\n\n";
    std::cout << "accuracy while learning:\n";
    for (auto accuracy : learningSetAccuracies) {
      std::cout << accuracy << ", ";
    }
    std::cout << "\n\n";
    std::cout << "accuracy after learning:\n";
    for (auto accuracy : testingSetAccuracies) {
      std::cout << accuracy << ", ";
    }
    std::cout << "\n\n";
  }
}

bool NeuralNetworkManager::testIteration(
    std::vector<double> &inputValues, std::vector<double> &desiredOutputs,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork, const bool learn,
    const bool debug) {

  auto &communicator = Shared::Communicator::Communicator::instance();

  // activate
  neuralNetwork.activate(inputValues);

  // compare to desired outputs
  std::vector<double> obtainedValues = neuralNetwork.outputValues();

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
    if (debug) {
      const auto dataBefore = neuralNetwork.getData();
    }
    neuralNetwork.backPropagete(desiredOutputs);
    if (debug) {
      const auto dataAfter = neuralNetwork.getData();

      communicator.postEvent(new Shared::Communicator::EvNeuralNetRunInfo(
          mNetworks.key(&neuralNetwork), dataAfter));

      // activate again with new weights and biases, but same inputs.
      // don't learn this time, just observe the change in output as a result of
      // the change in weights and biases.
      neuralNetwork.activate(inputValues);
    }
  }

  return pass;
}

} // namespace NodeNetwork
} // namespace Core
