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

  using NeuronData = typename Neuron<DataType>::Data;
  using NeuronConnectionData = typename NeuronConnection<DataType>::Data;
  using LayerData =
      std::vector<std::pair<NeuronData, std::vector<NeuronConnectionData>>>;
  using Data = std::vector<LayerData>;

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

  Data getData() {
    const auto &layers = this->layers();
    const auto layerCount = this->layerCount();
    Data data;
    data.reserve(layerCount);

    for (unsigned long layerIdx = 0; layerIdx < layerCount; ++layerIdx) {
      const auto *layer = layers.at(layerIdx);
      const auto &neurons = layer->neurons();
      const auto neuronCount = neurons.size();
      LayerData layerData;
      layerData.reserve(neuronCount);

      for (unsigned long neuronIdx = 0; neuronIdx < neuronCount; ++neuronIdx) {
        const auto *neuron = neurons.at(neuronIdx);
        const auto &outputConnections = neuron->outputNeuronConnections();
        const auto connectionCount = outputConnections.size();
        std::pair<NeuronData, std::vector<NeuronConnectionData>>
            layerNeuronData = std::make_pair(
                neuron->data(), std::vector<NeuronConnectionData>{});
        auto &neuronConnectionData = layerNeuronData.second;
        neuronConnectionData.reserve(connectionCount);

        for (unsigned long connectionIdx = 0; connectionIdx < connectionCount;
             ++connectionIdx) {
          const auto *connection = outputConnections.at(connectionIdx);
          neuronConnectionData.push_back(connection->data());
        }
        layerData.push_back(std::move(layerNeuronData));
      }
      data.push_back(std::move(layerData));
    }
    return data;
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
