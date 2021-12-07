#include "Node.h"
#include "NodeView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace NodeNetwork {

Node::Node(QObject *parent) : AbstractGraphicsItemController(parent) {}

QGraphicsItem *Node::createView(QGraphicsItem *parentView) {
  return new NodeView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
