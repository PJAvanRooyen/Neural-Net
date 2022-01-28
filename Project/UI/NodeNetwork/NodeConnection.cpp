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

  // WARNING!
  // For all derived node connection types, it must first initialize
  // its base as empty, then create its own view.
  // This is necessary so that the correct derived view is created instead of
  // the base view.
  auto *nodeConnectionView = view<NodeConnectionView>();
  sourceNode->view<NodeView>()->addOutputNodeConnection(nodeConnectionView);
  destNode->view<NodeView>()->addInputNodeConnection(nodeConnectionView);

  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
}

NodeConnection::NodeConnection()
    : AbstractGraphicsItemController(),
      Shared::NodeNetwork::AbstractNodeConnection(){};

QGraphicsItem *NodeConnection::createViewBase(QGraphicsItem *parentView) {
  return new NodeConnectionView(
      static_cast<Node *>(sourceNode())->view<NodeView>(),
      static_cast<Node *>(destinationNode())->view<NodeView>(), parentView);
}

} // namespace NodeNetwork
} // namespace UI
