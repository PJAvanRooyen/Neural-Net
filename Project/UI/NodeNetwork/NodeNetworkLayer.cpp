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

  auto *nodeController = static_cast<Node *>(node);
  nodeController->setParent(this);
  AbstractNodeNetworkLayer::addNode(node);

  view<NodeNetworkLayerView>()->addNode(
      static_cast<Node *>(node)->view<NodeView>());
}

void NodeNetworkLayer::addNodes(
    std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) {
  for (auto *node : nodes) {
    addNode(node);
  }
}

QGraphicsItem *NodeNetworkLayer::createViewBase(QGraphicsItem *parentView) {
  return new NodeNetworkLayerView(parentView);
}
} // namespace NodeNetwork
} // namespace UI
