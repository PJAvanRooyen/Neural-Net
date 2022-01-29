#ifndef NeuralNetTest_H
#define NeuralNetTest_H

#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkLayer.h"
#include "Shared/NodeNetwork/NodeNetworkFactory.h"

#include "IrisDataExtractor.h"
#include "NeuralNetTestHelper.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace Tests {

class NeuralNetTest {
public:
  NeuralNetTest();

  ~NeuralNetTest();

  static void logicGateTest();

  static void irisTest();

  static void irisDataToNetworkInputs(
      std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &learningSet,
      std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &testingSet,
      const unsigned long outputNodeCount = 3);

  static void
  irisTest(std::vector<std::pair<std::vector<double>, std::vector<double>>>
               &learningSet,
           std::vector<std::pair<std::vector<double>, std::vector<double>>>
               &testingSet,
           Core::NodeNetwork::NeuralNetwork<double> &neuralNet);

  static void
  test(std::vector<std::pair<std::vector<double> /*inputs*/,
                             std::vector<double> /*desiredOutputs*/>>
           learningSet,
       std::vector<std::pair<std::vector<double> /*inputs*/,
                             std::vector<double> /*desiredOutputs*/>>
           testingSet,
       Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
       const double valuePollingRate = 0.01, const bool debug = true);

  static bool
  testIteration(std::vector<double> &inputValues,
                std::vector<double> &desiredOutputs,
                Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                const bool learn, const bool debug);
};

void NeuralNetTest::logicGateTest() {
  // setup test
  const unsigned long learningIterations = 50000;
  const unsigned long testingIterations = 10000;
  const double valuesToPoll = 100;
  std::srand(unsigned(std::time(0)));

  // setup network
  const std::vector<unsigned long> shape = {2, 2};

  std::vector<std::pair<std::vector<double> /*inputs*/,
                        std::vector<double> /*desiredOutputs*/>>
      learningSet;
  learningSet.reserve(learningIterations);

  std::vector<std::pair<std::vector<double> /*inputs*/,
                        std::vector<double> /*desiredOutputs*/>>
      testingSet;
  testingSet.reserve(testingIterations);

  auto desiredOutputs = [](const std::vector<double> &inputs) {
    bool in0 = std::round(inputs[0]);
    bool in1 = std::round(inputs[1]);

    std::vector<double> desiredOutputs;
    desiredOutputs.push_back(in0 && !in1);
    desiredOutputs.push_back(!in0 && in1);

    return desiredOutputs;
  };

  auto inputValueGenerator =
      [desiredOutputs](
          std::vector<std::pair<std::vector<double> /*inputs*/,
                                std::vector<double> /*desiredOutputs*/>>
              &dataset,
          const unsigned long inputNodeCount, const unsigned long iterations) {
        for (unsigned long idx = 0; idx < iterations; ++idx) {
          std::vector<double> inputs;
          inputs.reserve(inputNodeCount);
          for (unsigned long nodeIdx = 0; nodeIdx < inputNodeCount; ++nodeIdx) {
            inputs[nodeIdx] = static_cast<double>(rand()) / RAND_MAX;
          }
          dataset[idx] = std::make_pair(inputs, desiredOutputs(inputs));
        }
      };

  // generate test data
  inputValueGenerator(learningSet, shape.front(), learningIterations);
  inputValueGenerator(testingSet, shape.front(), testingIterations);

  // create the network
  Shared::NodeNetwork::NodeNetworkFactory factory =
      Shared::NodeNetwork::NodeNetworkFactory();
  Shared::NodeNetwork::AbstractNodeNetwork *abstractNet =
      factory.createMeshNetwork<Core::NodeNetwork::NeuralNetwork<double>>(
          shape);
  Core::NodeNetwork::NeuralNetwork<double> &neuralNet =
      static_cast<Core::NodeNetwork::NeuralNetwork<double> &>(*abstractNet);

  // teach the network
  test(learningSet, testingSet, neuralNet, valuesToPoll);
}

void NeuralNetTest::irisTest() {
  // setup network
  const unsigned long inputNodeCount = 4;
  const unsigned long outputNodeCount = 3;
  const std::vector<unsigned long> shape = {inputNodeCount, 4, 4, 4,
                                            outputNodeCount};

  std::vector<std::pair<std::vector<double>, std::vector<double>>> learningSet;
  std::vector<std::pair<std::vector<double>, std::vector<double>>> testingSet;
  irisDataToNetworkInputs(learningSet, testingSet, outputNodeCount);

  // create the network
  Shared::NodeNetwork::NodeNetworkFactory factory =
      Shared::NodeNetwork::NodeNetworkFactory();
  Shared::NodeNetwork::AbstractNodeNetwork *abstractNet =
      factory.createMeshNetwork<Core::NodeNetwork::NeuralNetwork<double>>(
          shape);
  Core::NodeNetwork::NeuralNetwork<double> &neuralNet =
      static_cast<Core::NodeNetwork::NeuralNetwork<double> &>(*abstractNet);

  irisTest(learningSet, testingSet, neuralNet);
}

void NeuralNetTest::irisDataToNetworkInputs(
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &learningSet,
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &testingSet,
    const unsigned long outputNodeCount) {
  // setup test
  const unsigned long learningIterations = /*5000*/ 100;
  const unsigned long testingIterations = /*1000*/ 0;
  std::srand(unsigned(/*std::time(0)*/ 1));

  learningSet.reserve(learningIterations);
  testingSet.reserve(testingIterations);

  DataExtractor::DataExtractor::generateLearningAndTestingSets(
      learningSet, testingSet, outputNodeCount, learningIterations,
      testingIterations);
}

void NeuralNetTest::irisTest(
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>> &learningSet,
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>> &testingSet,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNet) {
  // teach the network
  const double valuesToPoll = 1;
  test(learningSet, testingSet, neuralNet, valuesToPoll);
}

void NeuralNetTest::test(
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>>
        learningSet,
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>>
        testingSet,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
    const double valuePollingRate, const bool debug) {

  const unsigned long poll =
      (learningSet.size() + testingSet.size()) / valuePollingRate;

  unsigned long correctCount = 0;
  std::vector<double> learningSetAccuracies;
  std::vector<double> testingSetAccuracies;

  if (debug) {
    std::cout << "learning set:\n";
  }
  for (unsigned long i = 0; i < learningSet.size(); ++i) {
    std::vector<double> inputs = learningSet[i].first;
    std::vector<double> desiredOutputs = learningSet[i].second;

    if (i != 0 && i % poll == 0) {
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

  if (debug) {
    std::cout << "testing set:\n";
  }
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
    std::cout << "learning set accuracies:\n";
    for (auto accuracy : learningSetAccuracies) {
      std::cout << accuracy << ", ";
    }
    std::cout << "\n\n";
    std::cout << "testing set accuracies:\n";
    for (auto accuracy : testingSetAccuracies) {
      std::cout << accuracy << ", ";
    }
    std::cout << "\n\n";
  }
}

bool NeuralNetTest::testIteration(
    std::vector<double> &inputValues, std::vector<double> &desiredOutputs,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork, const bool learn,
    const bool debug) {
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

  // show debug info
  if (debug) {
    std::cout << "pre-update:\n";
    //      Print::printWeights(layerConnections);
    //      Print::printBiases(layerNeurons);
    //      Print::printActivations(layerNeurons);
    Print::printSensitivities(neuralNetwork);
    //      Print::printErrors(outputLayer, desired);
  }

  // teach the network
  if (learn) {
    const auto dataBefore = neuralNetwork.getData();
    neuralNetwork.backPropagete(desiredOutputs);
    const auto dataAfter = neuralNetwork.getData();
  }

  if (learn && debug) {
    // activate again with new weights and biases, but same inputs.
    // don't learn this time, just observe the change in output as a result of
    // the change in weights and biases.
    neuralNetwork.activate(inputValues);

    // show debug info
    if (debug) {
      std::cout << "post-update:\n";
      //        Print::printWeights(layerConnections);
      //        Print::printBiases(layerNeurons);
      //        Print::printActivations(layerNeurons);
      Print::printSensitivities(neuralNetwork);
      //        Print::printErrors(outputLayer, desired);
    }
  }

  if (debug) {
    std::cout << "\n";
  }

  return pass;
}

} // namespace Tests

#endif // NeuralNetTest_H
