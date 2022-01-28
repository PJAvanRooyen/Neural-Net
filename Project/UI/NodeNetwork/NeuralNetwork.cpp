#include "NeuralNetwork.h"
#include "NeuralNetworkLayer.h"
#include "Neuron.h"
#include "NeuronConnection.h"

// test
#include "NodeNetworkLayerView.h"
// test

#include "NodeNetworkView.h"

namespace UI {
namespace NodeNetwork {

NeuralNetwork::NeuralNetwork(QObject *parent)
    : UI::NodeNetwork::NodeNetwork(parent) {}

Shared::NodeNetwork::AbstractNodeNetworkLayer *NeuralNetwork::addLayer() {
  auto *layer = new NeuralNetworkLayer(this);
  NodeNetwork::addLayer(layer);
  return layer;
}

Shared::NodeNetwork::AbstractNodeConnection *
NeuralNetwork::addConnection(NodeNetwork::AbstractNode *sourceNode,
                             NodeNetwork::AbstractNode *destinationNode) {
  auto *source = static_cast<Neuron *>(sourceNode);
  auto *destination = static_cast<Neuron *>(destinationNode);

  auto *nodeConnection = new NeuronConnection(source, destination, this);
  return nodeConnection;
}

void NeuralNetwork::setData(
    const Shared::NodeNetwork::NeuralNetworkData<double> &neuralNetData) {
  const auto &layers = this->layers();
  const auto layerCount = this->layerCount();

  for (unsigned long layerIdx = 0; layerIdx < layerCount; ++layerIdx) {
    auto *layer = static_cast<NeuralNetworkLayer *>(layers.at(layerIdx));
    const auto &nodes = layer->nodes();
    const auto neuronCount = nodes.size();
    const auto &layerData = neuralNetData[layerIdx];

    for (unsigned long neuronIdx = 0; neuronIdx < neuronCount; ++neuronIdx) {
      auto *neuron = static_cast<Neuron *>(nodes.at(neuronIdx));

      // set neuron data
      const auto &neuronData = layerData[neuronIdx].first;
      neuron->setData(neuronData);

      const auto &outputConnections = neuron->outputNodeConnections();
      const auto connectionCount = outputConnections.size();

      for (unsigned long connectionIdx = 0; connectionIdx < connectionCount;
           ++connectionIdx) {
        auto *connection = static_cast<NeuronConnection *>(
            outputConnections.at(connectionIdx));
        const auto &connectionData =
            layerData[neuronIdx].second.at(connectionIdx);
        connection->setData(connectionData);
      }
    }
  }
}
} // namespace NodeNetwork
} // namespace UI
