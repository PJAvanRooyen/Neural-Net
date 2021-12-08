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

  view<NodeNetworkLayerView>()->addNode(
      static_cast<Node *>(node)->view<NodeView>());
}

void NodeNetworkLayer::addNodes(
    std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) {
  AbstractNodeNetworkLayer::addNodes(nodes);

  for (auto *node : nodes) {
    view<NodeNetworkLayerView>()->addNode(
        static_cast<Node *>(node)->view<NodeView>());
  }
}

QGraphicsItem *NodeNetworkLayer::createViewBase(QGraphicsItem *parentView) {
  return new NodeNetworkLayerView(parentView);
}
} // namespace NodeNetwork
} // namespace UI
