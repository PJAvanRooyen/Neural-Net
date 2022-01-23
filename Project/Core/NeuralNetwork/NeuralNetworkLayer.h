#ifndef NeuralNetworkLayer_H
#define NeuralNetworkLayer_H

#include "Core/NodeNetwork/NodeNetworkLayer.h"

namespace Core {
namespace NodeNetwork {

template <typename DataType> class Neuron;

template <typename DataType>
class NeuralNetworkLayer : public Core::NodeNetwork::NodeNetworkLayer {
public:
  NeuralNetworkLayer() {}

  ~NeuralNetworkLayer() {}

  Shared::NodeNetwork::AbstractNode *addNode() override {
    auto *neuron = new Neuron<DataType>();
    this->addNeuron(neuron);
    return neuron;
  }

  void addNode(AbstractNode *node) override {
    AbstractNodeNetworkLayer::addNode(node);
  }

  void
  addNodes(std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) override {
    AbstractNodeNetworkLayer::addNodes(nodes);
  }

  void addNeuron(Neuron<DataType> *neuron) { this->addNode(neuron); }

  const std::vector<Neuron<DataType> *> &neurons() const {
    return reinterpret_cast<const std::vector<Neuron<DataType> *> &>(
        NodeNetworkLayer::nodes());
  }
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkLayer_H
