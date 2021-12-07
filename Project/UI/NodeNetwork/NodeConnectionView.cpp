#include "NodeConnectionView.h"
#include "NodeView.h"

#include <QPainter>
#include <QtMath>

namespace UI {
namespace NodeNetwork {

const qreal NodeConnectionView::kArrowSize = 10;

NodeConnectionView::NodeConnectionView(NodeView *sourceNodeView,
                                       NodeView *destinationNodeView,
                                       QGraphicsItem *parent)
    : QGraphicsItem(parent), Shared::NodeNetwork::AbstractNodeConnection(
                                 sourceNodeView, destinationNodeView) {
  setAcceptedMouseButtons(Qt::NoButton);
  sourceNode()->addInputNodeConnection(this);
  destinationNode()->addOutputNodeConnection(this);
  adjust();
}

void NodeConnectionView::adjust() {
  auto *source = sourceNode();
  auto *destination = destinationNode();

  if (!source || !destination)
    return;

  QLineF line(mapFromItem(static_cast<NodeView *>(source), 0, 0),
              mapFromItem(static_cast<NodeView *>(destination), 0, 0));
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
  auto *source = sourceNode();
  auto *destination = destinationNode();

  if (!source || !destination)
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
  auto *source = sourceNode();
  auto *destination = destinationNode();

  if (!source || !destination)
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

} // namespace NodeNetwork
} // namespace UI
