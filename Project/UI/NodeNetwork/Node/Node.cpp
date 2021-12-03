#include "Node.h"
#include "NeuronView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace Node {

Node::Node(QObject *parent) : AbstractGraphicsItemController(parent) {}

Node::~Node(){};

QGraphicsItem *Node::createView(QGraphicsItem *parentView) {
  return new NodeView(parentView);
}

} // namespace Node
} // namespace UI
