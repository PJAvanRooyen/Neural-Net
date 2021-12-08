#include "NodeConnection.h"
#include "Node.h"
#include "NodeConnectionView.h"
#include "NodeView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace NodeNetwork {

NodeConnection::NodeConnection(Node *sourceNode, Node *destNode,
                               AbstractGraphicsItemController *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeConnection() {

  mSource = sourceNode;
  mDestination = destNode;

  auto *nodeConnectionView = static_cast<NodeConnectionView *>(view());
  static_cast<NodeView *>(sourceNode->view())
      ->addOutputNodeConnection(nodeConnectionView);
  static_cast<NodeView *>(destNode->view())
      ->addInputNodeConnection(nodeConnectionView);

  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
};

QGraphicsItem *NodeConnection::createView(QGraphicsItem *parentView) {
  return new NodeConnectionView(
      static_cast<NodeView *>(static_cast<Node *>(sourceNode())->view()),
      static_cast<NodeView *>(static_cast<Node *>(destinationNode())->view()),
      parentView);
}

} // namespace NodeNetwork
} // namespace UI
