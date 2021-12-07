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

void NodeNetworkLayer::addNode(Shared::NodeNetwork::AbstractNode *node) {
  AbstractNodeNetworkLayer::addNode(node);

  static_cast<NodeNetworkLayerView *>(view())->addNode(
      static_cast<NodeView *>(static_cast<Node *>(node)->view()));
}

void NodeNetworkLayer::addNodes(
    std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) {
  AbstractNodeNetworkLayer::addNodes(nodes);

  for (auto *node : nodes) {
    static_cast<NodeNetworkLayerView *>(view())->addNode(
        static_cast<NodeView *>(static_cast<Node *>(node)->view()));
  }
}

QGraphicsItem *NodeNetworkLayer::createView(QGraphicsItem *parentView) {
  return new NodeNetworkLayerView(parentView);
}
} // namespace NodeNetwork
} // namespace UI
