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

  void addNeuron(Neuron<DataType> *neuron) { this->addNode(neuron); }

  const std::vector<Neuron<DataType> *> &neurons() const {
    return reinterpret_cast<const std::vector<Neuron<DataType> *> &>(
        NodeNetworkLayer::nodes());
  }

private:
  void addNode(AbstractNode *node) override {
    AbstractNodeNetworkLayer::addNode(node);
  }
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkLayer_H
