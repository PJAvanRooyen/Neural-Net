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

  auto *nodeConnectionView = view<NodeConnectionView>();
  sourceNode->view<NodeView>()->addOutputNodeConnection(nodeConnectionView);
  destNode->view<NodeView>()->addInputNodeConnection(nodeConnectionView);

  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
};

QGraphicsItem *NodeConnection::createViewBase(QGraphicsItem *parentView) {
  return new NodeConnectionView(
      static_cast<Node *>(sourceNode())->view<NodeView>(),
      static_cast<Node *>(destinationNode())->view<NodeView>(), parentView);
}

} // namespace NodeNetwork
} // namespace UI
