#include "NodeConnection.h"
#include "Node.h"
#include "NodeConnectionView.h"
#include "NodeView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace Node {

NodeConnection::NodeConnection(Node *sourceNode, Node *destNode,
                               QObject *parent)
    : AbstractGraphicsItemController(parent), mSource(sourceNode),
      mDestination(destNode){};

NodeConnection::~NodeConnection(){};

Node *NodeConnection::sourceNode() const { return mSource; }

Node *NodeConnection::destNode() const { return mDestination; }

QGraphicsItem *NodeConnection::createView(QGraphicsItem *parentView) {
  return new NodeConnectionView(static_cast<NodeView *>(mSource->view()),
                                static_cast<NodeView *>(mDestination->view()),
                                parentView);
}

} // namespace Node
} // namespace UI
