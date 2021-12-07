#include "NodeConnection.h"
#include "Node.h"
#include "NodeConnectionView.h"
#include "NodeView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace NodeNetwork {

NodeConnection::NodeConnection(Node *sourceNode, Node *destNode,
                               QObject *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeConnection(sourceNode, destNode){};

QGraphicsItem *NodeConnection::createView(QGraphicsItem *parentView) {
  return new NodeConnectionView(
      static_cast<NodeView *>(static_cast<Node *>(sourceNode())->view()),
      static_cast<NodeView *>(static_cast<Node *>(destinationNode())->view()),
      parentView);
}

} // namespace NodeNetwork
} // namespace UI
