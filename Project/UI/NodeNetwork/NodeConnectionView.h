#ifndef NodeConnectionView_H
#define NodeConnectionView_H

#include "Shared/NodeNetwork/AbstractNodeConnection.h"

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

class NodeView;

class NodeConnectionView : public QGraphicsItem,
                           public Shared::NodeNetwork::AbstractNodeConnection {
  static const qreal kArrowSize;

public:
  NodeConnectionView(NodeView *sourceNodeView, NodeView *destinationNodeView,
                     QGraphicsItem *parent = Q_NULLPTR);

  void adjust();

protected:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  QPointF mSourcePoint;
  QPointF mDestinationPoint;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeConnectionView_H
