#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Core/NeuralNetwork/Neuron.h"
#include "Core/NodeNetwork/NodeNetwork.h"

namespace Core {
namespace NodeNetwork {

template <typename DataType> class NeuralNetworkLayer;

template <typename DataType> class NeuralNetwork : public NodeNetwork {
public:
  NeuralNetwork() {}

  ~NeuralNetwork() {}

  const NeuralNetworkLayer<DataType> *
  layerAt(const unsigned long long layerIndex) const {
    return static_cast<const NeuralNetworkLayer<DataType> *>(
        NodeNetwork::layerAt(layerIndex));
  }

  const NeuralNetworkLayer<DataType> *inputLayer() const {
    return static_cast<const NeuralNetworkLayer<DataType> *>(
        NodeNetwork::inputLayer());
  }

  const NeuralNetworkLayer<DataType> *outputLayer() const {
    return static_cast<const NeuralNetworkLayer<DataType> *>(
        NodeNetwork::outputLayer());
  }

  const std::vector<NeuralNetworkLayer<DataType> *> &layers() const {
    return reinterpret_cast<
        const std::vector<NeuralNetworkLayer<DataType> *> &>(
        NodeNetwork::layers());
  }

  Shared::NodeNetwork::AbstractNodeNetworkLayer *addLayer() override {
    auto *layer = new NeuralNetworkLayer<DataType>();
    this->addLayer(layer);
    return layer;
  }

  void addLayer(Shared::NodeNetwork::AbstractNodeNetworkLayer *layer) override {
    AbstractNodeNetwork::addLayer(layer);
  }

  Shared::NodeNetwork::AbstractNodeConnection *
  addConnection(AbstractNode *sourceNode,
                AbstractNode *destinationNode) override {
    auto *source = static_cast<Neuron<DataType> *>(sourceNode);
    auto *destination = static_cast<Neuron<DataType> *>(destinationNode);

    auto *connection = new NeuronConnection<DataType>(source, destination);
    this->addConnection(connection);
    return connection;
  }

  void addConnection(
      Shared::NodeNetwork::AbstractNodeConnection *connection) override {
    AbstractNodeNetwork::addConnection(connection);
  }

  bool activate(const std::vector<DataType> &values) {
    deactivate();

    const bool valuesSet = setInputValues(values);

    const auto &outputNeurons = outputLayer()->neurons();

    for (auto *neuron : outputNeurons) {
      neuron->activate();
    }

    return valuesSet;
  }

  std::vector<DataType> outputValues() const {
    const auto &outputNeurons = outputLayer()->neurons();

    std::vector<DataType> obtainedValues;
    for (auto *neuron : outputNeurons) {
      obtainedValues.push_back(neuron->value());
    }

    return obtainedValues;
  }

  bool backPropagete(const std::vector<DataType> &values) {
    const bool valuesSet = setDesiredOutputValues(values);

    const auto &inputNeurons = inputLayer()->neurons();

    for (auto *neuron : inputNeurons) {
      neuron->backPropagate();
    }

    return valuesSet;
  }

private:
  void deactivate() {
    const auto &outputNeurons = outputLayer()->neurons();

    for (auto *neuron : outputNeurons) {
      neuron->deActivate();
    }
  }

  bool setInputValues(const std::vector<DataType> &values) {
    const auto &inputNeurons = inputLayer()->neurons();

    auto valueCount = values.size();
    auto inputNeuronCount = inputNeurons.size();

    for (auto neuronIdx = 0; neuronIdx < inputNeuronCount; ++neuronIdx) {
      if (neuronIdx < valueCount) {
        inputNeurons[neuronIdx]->setValue(values[neuronIdx]);
      }
    }

    return inputNeuronCount == valueCount;
  }

  bool setDesiredOutputValues(const std::vector<DataType> &values) {
    const auto &outputNeurons = outputLayer()->neurons();

    auto valueCount = values.size();
    auto outputNeuronCount = outputNeurons.size();

    for (unsigned long neuronIdx = 0; neuronIdx < outputNeuronCount;
         ++neuronIdx) {
      if (neuronIdx < valueCount) {
        DataType desiredValue = values[neuronIdx];
        outputNeurons[neuronIdx]->setDesiredActivation(desiredValue);
      }
    }

    return outputNeuronCount == valueCount;
  }
};
} // namespace NodeNetwork
} // namespace Core
#endif // NeuralNetwork_H
