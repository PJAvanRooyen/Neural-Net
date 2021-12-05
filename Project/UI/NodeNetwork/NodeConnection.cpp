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
    : AbstractGraphicsItemController(parent), mSource(sourceNode),
      mDestination(destNode) {
  // note: connections are only done in a forward direction.
  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
};

NodeConnection::~NodeConnection(){};

Node *NodeConnection::sourceNode() const { return mSource; }

Node *NodeConnection::destinationNode() const { return mDestination; }

QGraphicsItem *NodeConnection::createView(QGraphicsItem *parentView) {
  return new NodeConnectionView(static_cast<NodeView *>(mSource->view()),
                                static_cast<NodeView *>(mDestination->view()),
                                parentView);
}

} // namespace NodeNetwork
} // namespace UI
