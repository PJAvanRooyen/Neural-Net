#ifndef NeuralNetTest_H
#define NeuralNetTest_H

#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkLayer.h"
#include "Shared/NodeNetwork/NodeNetworkFactory.h"

#include "IrisDataExtractor.h"
#include "NeuralNetTestHelper.h"

#include <iostream>
#include <vector>

namespace Tests {

class NeuralNetTest {
  typedef bool (*DesiredOutputsComparator)(const std::vector<double> &in,
                                           const std::vector<double> &out,
                                           std::vector<double> &desired);

  typedef std::vector<double> (*InputValueGenerator)(
      const unsigned long long inputNodeCount);

public:
  NeuralNetTest();

  ~NeuralNetTest();

  static void logicGateTest();

  static void irisTest();

  static void test(const InputValueGenerator &inputValueGenerator,
                   Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                   const DesiredOutputsComparator &desiredOutputsComparator,
                   const unsigned long long learningIterations = 500,
                   const double valuePollingRate = 0.01,
                   const bool debug = true);

  static bool
  testIteration(std::vector<double> &inputValues,
                Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                const DesiredOutputsComparator &desiredOutputsComparator,
                const bool learn, const bool debug);
};

void NeuralNetTest::logicGateTest() {
  srand(1);

  auto inputValueGenerator = [](const unsigned long long inputNodeCount) {
    std::vector<double> inputs;
    for (unsigned long long nodeIdx = 0; nodeIdx < inputNodeCount; ++nodeIdx) {
      inputs.push_back(static_cast<double>(rand()) / RAND_MAX);
    }

    return inputs;
  };

  auto compareWithDesiredOutputs =
      [](const std::vector<double> &inputs,
         const std::vector<double> &obtainedOutputs,
         std::vector<double> &desiredOutputs) {
        bool in0 = inputs[0];
        bool in1 = inputs[1];

        desiredOutputs.push_back(in0 && !in1);
        desiredOutputs.push_back(!in0 && in1);

        std::vector<double> obtainedBools;
        for (const double value : obtainedOutputs) {
          bool obtainedValue = std::round(value);
          obtainedBools.push_back(obtainedValue);
        }

        return desiredOutputs == obtainedBools;
      };

  Shared::NodeNetwork::NodeNetworkFactory factory =
      Shared::NodeNetwork::NodeNetworkFactory();
  Shared::NodeNetwork::AbstractNodeNetwork *abstractNet =
      factory.createMeshNetwork<Core::NodeNetwork::NeuralNetwork<double>>(
          {2, 2, 2});
  Core::NodeNetwork::NeuralNetwork<double> &neuralNet =
      static_cast<Core::NodeNetwork::NeuralNetwork<double> &>(*abstractNet);

  // teach the network
  test(inputValueGenerator, neuralNet, compareWithDesiredOutputs);
}

void NeuralNetTest::irisTest() {
  auto dataset = DataExtractor::DataExtractor::extract();

  Shared::NodeNetwork::NodeNetworkFactory factory =
      Shared::NodeNetwork::NodeNetworkFactory();
  Shared::NodeNetwork::AbstractNodeNetwork *abstractNet =
      factory.createMeshNetwork<Core::NodeNetwork::NeuralNetwork<double>>(
          {2, 2, 2});
  Core::NodeNetwork::NeuralNetwork<double> *neuralNet =
      static_cast<Core::NodeNetwork::NeuralNetwork<double> *>(abstractNet);

  // teach the network
  const bool debug = true;
  Q_UNUSED(neuralNet)
  Q_UNUSED(debug)
}

void NeuralNetTest::test(
    const InputValueGenerator &inputValueGenerator,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
    const DesiredOutputsComparator &desiredOutputsComparator,
    const unsigned long long learningIterations, const double valuePollingRate,
    const bool debug) {
  const unsigned long long poll = learningIterations * valuePollingRate;

  unsigned long long correctCount = 0;
  std::vector<double> accuracies;

  std::vector<double> inputs;
  for (unsigned long long i = 0; i < learningIterations * 4; ++i) {
    inputs = inputValueGenerator(neuralNetwork.inputLayer()->size());

    if (i != 0 && i % poll == 0) {
      double accuracy = 100.0 * correctCount / poll;
      accuracies.push_back(accuracy);
      correctCount = 0;
      bool correct = testIteration(inputs, neuralNetwork,
                                   desiredOutputsComparator, true, true);
      if (correct) {
        ++correctCount;
      }
    } else {
      // teach the network
      bool correct = testIteration(inputs, neuralNetwork,
                                   desiredOutputsComparator, true, false);
      if (correct) {
        ++correctCount;
      }
    }
  }

  if (debug) {
    std::cout << "accuracies: ";
    for (auto accuracy : accuracies) {
      std::cout << accuracy << ", ";
    }
    std::cout << "\n\n";
  }
}

bool NeuralNetTest::testIteration(
    std::vector<double> &inputValues,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
    const DesiredOutputsComparator &desiredOutputsComparator, const bool learn,
    const bool debug) {
  // activate
  neuralNetwork.activate(inputValues);

  // compare to desired outputs
  std::vector<double> obtainedValues = neuralNetwork.outputValues();

  std::vector<double> desiredValues;
  bool result =
      desiredOutputsComparator(inputValues, obtainedValues, desiredValues);

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
    neuralNetwork.backPropagete(desiredValues);
  }

  if (learn && debug) {
    // activate
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

  return result;
}

} // namespace Tests

#endif // NeuralNetTest_H
