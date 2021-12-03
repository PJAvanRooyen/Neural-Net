#include "NodeView.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

namespace UI {
namespace Node {

NodeView::NodeView(QGraphicsItem *parent) : QGraphicsItem(parent) {
  setFlag(ItemIsMovable);
  setFlag(ItemSendsGeometryChanges);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

QRectF NodeView::boundingRect() const {
  qreal adjust = 2;
  return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath NodeView::shape() const {
  QPainterPath path;
  path.addEllipse(-10, -10, 20, 20);
  return path;
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *) {
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::darkGray);
  painter->drawEllipse(-7, -7, 20, 20);

  QRadialGradient gradient(-3, -3, 10);
  if (option->state & QStyle::State_Sunken) {
    gradient.setCenter(3, 3);
    gradient.setFocalPoint(3, 3);
    gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
    gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
  } else {
    gradient.setColorAt(0, Qt::yellow);
    gradient.setColorAt(1, Qt::darkYellow);
  }
  painter->setBrush(gradient);

  painter->setPen(QPen(Qt::black, 0));
  painter->drawEllipse(-10, -10, 20, 20);
}

QVariant NodeView::itemChange(GraphicsItemChange change,
                              const QVariant &value) {
  //  switch (change) {
  //  case ItemPositionHasChanged:
  //    for (Edge *edge : qAsConst(edgeList))
  //      edge->adjust();
  //    graph->itemMoved();
  //    break;
  //  default:
  //    break;
  //  };

  return QGraphicsItem::itemChange(change, value);
}

void NodeView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  update();
  QGraphicsItem::mousePressEvent(event);
}

void NodeView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}
} // namespace Node
} // namespace UI
