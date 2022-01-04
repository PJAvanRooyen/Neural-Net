#include "NeuralNetworkFactory.h"
#include "UI/NodeNetwork/Neuron.h"
#include "UI/NodeNetwork/NodeConnection.h"
#include "UI/NodeNetwork/NodeNetwork.h"
#include "UI/NodeNetwork/NodeNetworkLayer.h"

namespace UI {
namespace NodeNetwork {

NeuralNetworkFactory::NeuralNetworkFactory() {}

NeuralNetworkFactory::~NeuralNetworkFactory() {}

Shared::NodeNetwork::AbstractNodeNetwork *
NeuralNetworkFactory::createNodeNetwork() const {
  return new NodeNetwork();
}

Shared::NodeNetwork::AbstractNodeNetworkLayer *
NeuralNetworkFactory::addNodeNetworkLayer(
    Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork) const {
  auto *nodeNet = static_cast<NodeNetwork *>(nodeNetwork);
  auto *layer = new NodeNetworkLayer(nodeNet);
  nodeNet->addLayer(layer);
  return layer;
}

Shared::NodeNetwork::AbstractNode *NeuralNetworkFactory::addNode(
    Shared::NodeNetwork::AbstractNodeNetworkLayer *nodeNetworkLayer) const {
  auto *nodeNetLayer = static_cast<NodeNetworkLayer *>(nodeNetworkLayer);
  auto *neuron = new Neuron(nodeNetLayer);
  nodeNetLayer->addNode(neuron);
  return neuron;
}

Shared::NodeNetwork::AbstractNodeConnection *
NeuralNetworkFactory::addNodeConnection(
    Shared::NodeNetwork::AbstractNode *sourceNode,
    Shared::NodeNetwork::AbstractNode *destinationNode,
    Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork) const {
  auto *nodeNet = static_cast<NodeNetwork *>(nodeNetwork);
  auto *sourceNeuron = static_cast<Neuron *>(sourceNode);
  auto *destinationNeuron = static_cast<Neuron *>(destinationNode);

  auto *neuronConnection =
      new NodeConnection(sourceNeuron, destinationNeuron, nodeNet);
  nodeNet->addNodeConnection(neuronConnection);
  return neuronConnection;
}
} // namespace NodeNetwork
} // namespace UI
