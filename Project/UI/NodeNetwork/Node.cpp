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

QGraphicsItem *Node::createView(QGraphicsItem *parentView) {
  return new NodeView(parentView);
}

void Node::addInputNodeConnection(
    Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) {
  AbstractNode::addInputNodeConnection(nodeConnection);

  static_cast<NodeView *>(view())->addInputNodeConnection(
      static_cast<NodeConnectionView *>(
          static_cast<NodeConnection *>(nodeConnection)->view()));
}

void Node::addInputNodeConnections(
    std::vector<Shared::NodeNetwork::AbstractNodeConnection *>
        &nodeConnections) {
  AbstractNode::addInputNodeConnections(nodeConnections);

  for (auto *nodeConnection : nodeConnections) {
    static_cast<NodeView *>(view())->addInputNodeConnection(
        static_cast<NodeConnectionView *>(
            static_cast<NodeConnection *>(nodeConnection)->view()));
  }
}

void Node::addOutputNodeConnection(
    Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) {
  AbstractNode::addOutputNodeConnection(nodeConnection);

  static_cast<NodeView *>(view())->addOutputNodeConnection(
      static_cast<NodeConnectionView *>(
          static_cast<NodeConnection *>(nodeConnection)->view()));
}

void Node::addOutputNodeConnections(
    std::vector<Shared::NodeNetwork::AbstractNodeConnection *>
        &nodeConnections) {
  AbstractNode::addOutputNodeConnections(nodeConnections);

  for (auto *nodeConnection : nodeConnections) {
    static_cast<NodeView *>(view())->addOutputNodeConnection(
        static_cast<NodeConnectionView *>(
            static_cast<NodeConnection *>(nodeConnection)->view()));
  }
}

} // namespace NodeNetwork
} // namespace UI
