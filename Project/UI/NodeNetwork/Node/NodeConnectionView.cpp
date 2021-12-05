#include "NodeConnectionView.h"
#include "NodeView.h"

#include <QPainter>
#include <QtMath>

namespace UI {
namespace Node {

const qreal NodeConnectionView::kArrowSize = 10;

NodeConnectionView::NodeConnectionView(NodeView *sourceNode, NodeView *destNode,
                                       QGraphicsItem *parent)
    : QGraphicsItem(parent), mSource(sourceNode), mDestination(destNode) {
  setAcceptedMouseButtons(Qt::NoButton);
  mSource->addNodeConnection(this);
  mDestination->addNodeConnection(this);
  adjust();
}

NodeView *NodeConnectionView::sourceNode() const { return mSource; }

NodeView *NodeConnectionView::destNode() const { return mDestination; }

void NodeConnectionView::adjust() {
  if (!mSource || !mDestination)
    return;

  QLineF line(mapFromItem(mSource, 0, 0), mapFromItem(mDestination, 0, 0));
  qreal length = line.length();

  prepareGeometryChange();

  if (length > qreal(20.)) {
    QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
    sourcePoint = line.p1() + edgeOffset;
    destPoint = line.p2() - edgeOffset;
  } else {
    sourcePoint = destPoint = line.p1();
  }
}

QRectF NodeConnectionView::boundingRect() const {
  if (!mSource || !mDestination)
    return QRectF();

  qreal penWidth = 1;
  qreal extra = (penWidth + kArrowSize) / 2.0;

  return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                    destPoint.y() - sourcePoint.y()))
      .normalized()
      .adjusted(-extra, -extra, extra, extra);
}

void NodeConnectionView::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *) {
  if (!mSource || !mDestination)
    return;

  QLineF line(sourcePoint, destPoint);
  if (qFuzzyCompare(line.length(), qreal(0.)))
    return;

  // Draw the line itself
  painter->setPen(
      QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawLine(line);

  painter->setBrush(Qt::black);

  // Draw the arrows
  double angle = std::atan2(-line.dy(), line.dx());

  // source arrow
  {
    //  QPointF sourceArrowP1 =
    //      sourcePoint + QPointF(sin(angle + M_PI / 3) * kArrowSize,
    //                            cos(angle + M_PI / 3) * kArrowSize);
    //  QPointF sourceArrowP2 =
    //      sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * kArrowSize,
    //                            cos(angle + M_PI - M_PI / 3) * kArrowSize);

    painter->drawPolygon(QPolygonF()
                         << line.p1() /*<< sourceArrowP1 << sourceArrowP2*/);
  }

  // destination arrow
  {
    QPointF destArrowP1 =
        destPoint + QPointF(sin(angle - M_PI / 3) * kArrowSize,
                            cos(angle - M_PI / 3) * kArrowSize);
    QPointF destArrowP2 =
        destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * kArrowSize,
                            cos(angle - M_PI + M_PI / 3) * kArrowSize);

    painter->drawPolygon(QPolygonF()
                         << line.p2() << destArrowP1 << destArrowP2);
  }
}

} // namespace Node
} // namespace UI
