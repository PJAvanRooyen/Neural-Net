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
  setZValue(3);
}

void NodeConnectionView::adjust() {
  auto *source = sourceNode();
  auto *destination = destinationNode();

  if (!source || !destination)
    return;

  NodeView *sourceNode = static_cast<NodeView *>(source);
  NodeView *destinationNode = static_cast<NodeView *>(destination);

  QLineF line(mapFromItem(sourceNode, 0, 0),
              mapFromItem(destinationNode, 0, 0));
  qreal length = line.length();

  prepareGeometryChange();

  if (length > qreal(20.)) {
    QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
    mSourcePoint = line.p1() + edgeOffset;
    mDestinationPoint = line.p2() - edgeOffset;
  } else {
    mSourcePoint = mDestinationPoint = line.p1();
  }
}

QRectF NodeConnectionView::boundingRect() const {
  auto *source = sourceNode();
  auto *destination = destinationNode();

  if (!source || !destination)
    return QRectF();

  qreal penWidth = 1;
  qreal extra = (penWidth + kArrowSize) / 2.0;

  return QRectF(mSourcePoint, QSizeF(mDestinationPoint.x() - mSourcePoint.x(),
                                     mDestinationPoint.y() - mSourcePoint.y()))
      .normalized()
      .adjusted(-extra, -extra, extra, extra);
}

void NodeConnectionView::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *) {
  auto *source = sourceNode();
  auto *destination = destinationNode();

  if (!source || !destination)
    return;

  QLineF line(mSourcePoint, mDestinationPoint);
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

      //    painter->drawPolygon(QPolygonF()
      //                         << line.p1() /*<< sourceArrowP1 <<
      //                         sourceArrowP2*/);
  }

  // destination arrow
  {
    QPointF destArrowP1 =
        mDestinationPoint + QPointF(sin(angle - M_PI / 3) * kArrowSize,
                                    cos(angle - M_PI / 3) * kArrowSize);
    QPointF destArrowP2 =
        mDestinationPoint + QPointF(sin(angle - M_PI + M_PI / 3) * kArrowSize,
                                    cos(angle - M_PI + M_PI / 3) * kArrowSize);

    painter->drawPolygon(QPolygonF()
                         << line.p2() << destArrowP1 << destArrowP2);
  }
}

} // namespace NodeNetwork
} // namespace UI
