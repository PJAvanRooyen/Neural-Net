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

  static void singleIterationTest();
};

void NeuralNetTest::singleIterationTest() {
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
  Core::DataExtractor::DataExtractor::generateLearningAndTestingSets(
      learningSet, testingSet);

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
} // namespace Tests

#endif // NeuralNetTest_H
