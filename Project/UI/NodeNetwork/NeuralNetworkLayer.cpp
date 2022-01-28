#include "NeuralNetworkLayer.h"
#include "Neuron.h"
#include "NeuronView.h"
#include "NodeNetworkLayerView.h"

namespace UI {
namespace NodeNetwork {

NeuralNetworkLayer::NeuralNetworkLayer(QObject *parent)
    : UI::NodeNetwork::NodeNetworkLayer(parent) {}

Shared::NodeNetwork::AbstractNode *NeuralNetworkLayer::addNode() {
  auto *node = new Neuron(this);
  addNeuron(node);
  return node;
}

void NeuralNetworkLayer::addNeuron(Neuron *neuron) {
  NodeNetworkLayer::addNode<NodeNetworkLayerView, NeuronView>(neuron);
}
} // namespace NodeNetwork
} // namespace UI
