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
  layer(const unsigned long long layerIdx) const {
    return static_cast<const NeuralNetworkLayer<DataType> *>(
        NodeNetwork::layer(layerIdx));
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
};
} // namespace NodeNetwork
} // namespace Core
#endif // NeuralNetwork_H
