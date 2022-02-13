#ifndef NeuralNetTest_H
#define NeuralNetTest_H

#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkFactory.h"
#include "Core/NeuralNetwork/NeuralNetworkLayer.h"
#include "Core/NeuralNetwork/NeuralNetworkManager.h"

#include "Core/NeuralNetwork/IrisDataExtractor.h"
#include "Core/NeuralNetwork/NeuralNetworkTester.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace Tests {

class NeuralNetTest {
public:
  NeuralNetTest();

  ~NeuralNetTest();

  static void logicGateTest();

  static void singleIterationTest();

  static void irisTest();

  static void irisDataToNetworkInputs(
      std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &learningSet,
      std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &testingSet,
      const unsigned long inputNodeCount,
      const unsigned long learningIterations,
      const unsigned long testingIterations,
      const std::optional<unsigned long> dataSeed);

  static void
  irisTest(std::vector<std::pair<std::vector<double>, std::vector<double>>>
               &learningSet,
           std::vector<std::pair<std::vector<double>, std::vector<double>>>
               &testingSet,
           Core::NodeNetwork::NeuralNetwork<double> &neuralNet);
};

void NeuralNetTest::logicGateTest() {
  // setup test
  const unsigned long learningIterations = 50000;
  const unsigned long testingIterations = 10000;
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
  Core::NodeNetwork::NeuralNetworkTester::test(learningSet, testingSet, QUuid(),
                                               neuralNet, true);
}

void NeuralNetTest::singleIterationTest() {
  // setup test
  quint8 iteratrions = 1;
  quint8 dataSeed = 2; // = 6.7,3.0,5.2,2.3,Iris-virginica

  // setup network
  quint8 networkSeed = 1;
  double learningRate = 0.01;
  const std::vector<unsigned long> shape = {4, 3, 3};

  // create the network
  Core::NodeNetwork::NeuralNetworkFactory factory =
      Core::NodeNetwork::NeuralNetworkFactory();
  auto *neuralNetwork =
      factory.createMeshNetwork<double>(shape, learningRate, networkSeed);

  // create the test data
  std::vector<std::pair<std::vector<double> /*inputs*/,
                        std::vector<double> /*desiredOutputs*/>>
      learningSet;
  std::vector<std::pair<std::vector<double>, std::vector<double>>> testingSet;
  irisDataToNetworkInputs(learningSet, testingSet, shape.front(), iteratrions,
                          0, dataSeed);

  Shared::NodeNetwork::NeuralNetworkData<double> initialData =
      neuralNetwork->getData();

  Core::NodeNetwork::NeuralNetworkTester::testIteration(
      learningSet.front().first, learningSet.front().second, *neuralNetwork,
      true);

  Shared::NodeNetwork::NeuralNetworkData<double> updatedData =
      neuralNetwork->getData();

  // ___output layer___
  const auto &updatedOutputLayer = updatedData[initialData.size() - 1];
  for (unsigned long neuronIdx = 0; neuronIdx < updatedOutputLayer.size();
       ++neuronIdx) {
    const auto &updatedNeuronData = updatedOutputLayer[neuronIdx].first;

    // verify sensitivity
    // for output neurons:
    // sensitivity = costFuncDerivative * activationFuncDerivative
    // sensitivity = (Pk - Ak) * g'(Ak)
    // sensitivity = (desiredOutput - activationValue) * {
    // sigmoid(activationValue) * [1 - sigmoid(activationValue) ] }
    double costDer = updatedNeuronData.desiredActivation.value() -
                     updatedNeuronData.activation.value();
    double sigmoid =
        1.0 / (1.0 + std::exp(-updatedNeuronData.activation.value()));
    double sigmoidDer = sigmoid * (1.0 - sigmoid);
    double sensitivity = costDer * sigmoidDer;
    Q_ASSERT(sensitivity == updatedNeuronData.sensitivity.value());
  }

  //___hidden layers___
  for (unsigned long layerIdx = initialData.size() - 2; layerIdx >= 1;
       --layerIdx) {
    const auto &initialLayer = initialData[layerIdx];
    const auto &updatedLayer = updatedData[layerIdx];
    for (unsigned long neuronIdx = 0; neuronIdx < initialLayer.size();
         ++neuronIdx) {
      const auto &initialNeuronData = initialLayer[neuronIdx].first;
      const auto &updatedNeuronData = updatedLayer[neuronIdx].first;
      // verify sensitivity
      // for hidden neurons:
      // sensitivity = activationFuncDerivative * sum ( outputConnectionWeight *
      // outputNeuronSensitivity )
      double sigmoid =
          1.0 / (1.0 + std::exp(-updatedNeuronData.activation.value()));
      double sigmoidDer = sigmoid * (1.0 - sigmoid);
      const auto &updatedConnectionsData = updatedLayer[neuronIdx].second;
      double outputSensitivitySum = 0;
      for (unsigned long connectionIdx = 0;
           connectionIdx < updatedConnectionsData.size(); ++connectionIdx) {
        const auto &updatedConnectionData =
            updatedConnectionsData[connectionIdx];
        const auto &nextLayerData = updatedData[layerIdx + 1];
        const auto &nextLayerNeuronData = nextLayerData[connectionIdx].first;

        // NOTE! using the updated weight to calculate lower layer neuron's
        // sensitivity.
        outputSensitivitySum += updatedConnectionData.weight *
                                nextLayerNeuronData.sensitivity.value();
      }
      double sensitivity = sigmoidDer * outputSensitivitySum;
      Q_ASSERT(sensitivity == updatedNeuronData.sensitivity.value());

      // verify bias
      double updatedBias =
          initialNeuronData.bias.value() +
          learningRate * updatedNeuronData.sensitivity.value() * 1.0;
      Q_ASSERT(updatedBias == updatedNeuronData.bias.value());

      // verify connection weights
      const auto &initialConnectionsData = initialLayer[neuronIdx].second;
      for (unsigned long connectionIdx = 0;
           connectionIdx < initialConnectionsData.size(); ++connectionIdx) {
        const auto &initialConnectionData =
            initialConnectionsData[connectionIdx];
        const auto &updatedConnectionData =
            updatedConnectionsData[connectionIdx];
        const auto &nextLayerData = updatedData[layerIdx + 1];
        const auto &nextLayerNeuronData = nextLayerData[connectionIdx].first;
        // verify weight
        double updatedWeight = initialConnectionData.weight +
                               learningRate *
                                   nextLayerNeuronData.sensitivity.value() *
                                   updatedNeuronData.activation.value();
        Q_ASSERT(updatedWeight == updatedConnectionData.weight);
      }
    }
  }
}

void NeuralNetTest::irisTest() {
  // setup network
  const unsigned long inputNodeCount = 4;
  const unsigned long outputNodeCount = 3;
  const std::vector<unsigned long> shape = {inputNodeCount, 4, 4, 4,
                                            outputNodeCount};
  const ulong learningIterations = 5000;
  const ulong testingIterations = 1000;
  const std::optional<ulong> dataSeed = std::nullopt;

  std::vector<std::pair<std::vector<double>, std::vector<double>>> learningSet;
  std::vector<std::pair<std::vector<double>, std::vector<double>>> testingSet;
  irisDataToNetworkInputs(learningSet, testingSet, inputNodeCount,
                          learningIterations, testingIterations, dataSeed);

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
    const unsigned long inputNodeCount, const unsigned long learningIterations,
    const unsigned long testingIterations,
    const std::optional<unsigned long> dataSeed = std::nullopt) {
  // setup test
  std::srand(dataSeed.has_value() ? dataSeed.value() : ulong(std::time(0)));

  learningSet.reserve(learningIterations);
  testingSet.reserve(testingIterations);

  Core::DataExtractor::DataExtractor extractor;
  extractor.generateLearningAndTestingSets(learningSet, testingSet,
                                           inputNodeCount, learningIterations,
                                           testingIterations);
}

void NeuralNetTest::irisTest(
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>> &learningSet,
    std::vector<std::pair<std::vector<double> /*inputs*/,
                          std::vector<double> /*desiredOutputs*/>> &testingSet,
    Core::NodeNetwork::NeuralNetwork<double> &neuralNet) {
  Core::NodeNetwork::NeuralNetworkTester::test(learningSet, testingSet, QUuid(),
                                               neuralNet, true);
}
} // namespace Tests

#endif // NeuralNetTest_H
