#include "NodeNetwork.h"
#include "Node.h"
#include "NodeConnection.h"
#include "NodeNetworkLayer.h"
#include "NodeNetworkLayerView.h"
#include "NodeNetworkView.h"

namespace UI {
namespace NodeNetwork {

NodeNetwork::NodeNetwork(QObject *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeNetwork() {}

void NodeNetwork::addLayer(
    Shared::NodeNetwork::AbstractNodeNetworkLayer *layer) {
  AbstractNodeNetwork::addLayer(layer);

  view<NodeNetworkView>()->addLayer(
      static_cast<NodeNetworkLayer *>(layer)->view<NodeNetworkLayerView>());
}

void NodeNetwork::addLayers(
    std::vector<Shared::NodeNetwork::AbstractNodeNetworkLayer *> &layers) {
  AbstractNodeNetwork::addLayers(layers);

  for (auto *layer : layers) {
    view<NodeNetworkView>()->addLayer(
        static_cast<NodeNetworkLayer *>(layer)->view<NodeNetworkLayerView>());
  }
}

Shared::NodeNetwork::AbstractNodeNetworkLayer *NodeNetwork::addLayer() {
  auto *layer = new NodeNetworkLayer(this);
  this->addLayer(layer);
  return layer;
}

Shared::NodeNetwork::AbstractNodeConnection *
NodeNetwork::addConnection(NodeNetwork::AbstractNode *sourceNode,
                           NodeNetwork::AbstractNode *destinationNode) {
  auto *source = static_cast<Node *>(sourceNode);
  auto *destination = static_cast<Node *>(destinationNode);

  auto *nodeConnection = new NodeConnection(source, destination, this);
  this->addConnection(nodeConnection);
  return nodeConnection;
}

void NodeNetwork::addConnection(
    Shared::NodeNetwork::AbstractNodeConnection *connection) {
  AbstractNodeNetwork::addConnection(connection);
}

QGraphicsItem *NodeNetwork::createViewBase(QGraphicsItem *parentView) {
  return new NodeNetworkView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
