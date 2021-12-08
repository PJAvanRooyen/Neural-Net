#include "Node.h"
#include "NodeConnection.h"
#include "NodeConnectionView.h"
#include "NodeView.h"
#include "Shared/NodeNetwork/AbstractNodeConnection.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace NodeNetwork {

Node::Node(QObject *parent) : AbstractGraphicsItemController(parent) {}

void Node::addInputNodeConnection(
    Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) {
  AbstractNode::addInputNodeConnection(nodeConnection);

  view<NodeView>()->addInputNodeConnection(static_cast<NodeConnectionView *>(
      static_cast<NodeConnection *>(nodeConnection)
          ->view<NodeConnectionView>()));
}

void Node::addInputNodeConnections(
    std::vector<Shared::NodeNetwork::AbstractNodeConnection *>
        &nodeConnections) {
  AbstractNode::addInputNodeConnections(nodeConnections);

  for (auto *nodeConnection : nodeConnections) {
    view<NodeView>()->addInputNodeConnection(
        static_cast<NodeConnection *>(nodeConnection)
            ->view<NodeConnectionView>());
  }
}

void Node::addOutputNodeConnection(
    Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) {
  AbstractNode::addOutputNodeConnection(nodeConnection);

  view<NodeView>()->addOutputNodeConnection(
      static_cast<NodeConnection *>(nodeConnection)
          ->view<NodeConnectionView>());
}

void Node::addOutputNodeConnections(
    std::vector<Shared::NodeNetwork::AbstractNodeConnection *>
        &nodeConnections) {
  AbstractNode::addOutputNodeConnections(nodeConnections);

  for (auto *nodeConnection : nodeConnections) {
    view<NodeView>()->addOutputNodeConnection(
        static_cast<NodeConnection *>(nodeConnection)
            ->view<NodeConnectionView>());
  }
}

QGraphicsItem *Node::createViewBase(QGraphicsItem *parentView) {
  return new NodeView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
