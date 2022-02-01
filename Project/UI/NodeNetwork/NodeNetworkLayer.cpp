#include "NodeNetworkLayer.h"
#include "Node.h"
#include "NodeConnection.h"
#include "NodeNetworkLayerView.h"
#include "NodeView.h"

namespace UI {
namespace NodeNetwork {

NodeNetworkLayer::NodeNetworkLayer(QObject *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeNetworkLayer() {}

Shared::NodeNetwork::AbstractNode *NodeNetworkLayer::addNode() {
  auto *node = new Node(this);
  addNode<NodeNetworkLayerView, NodeView>(node);
  return node;
}

QGraphicsItem *NodeNetworkLayer::createView(QGraphicsItem *parentView) {
  return new NodeNetworkLayerView(parentView);
}
} // namespace NodeNetwork
} // namespace UI
