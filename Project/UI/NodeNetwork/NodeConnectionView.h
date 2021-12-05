#ifndef NodeConnectionView_H
#define NodeConnectionView_H

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

class NodeView;

class NodeConnectionView : public QGraphicsItem {
  static const qreal kArrowSize;

public:
  NodeConnectionView(NodeView *sourceNode, NodeView *destNode,
                     QGraphicsItem *parent = Q_NULLPTR);

  NodeView *sourceNode() const;
  NodeView *destNode() const;

  void adjust();

  enum { Type = UserType + 2 };
  int type() const override { return Type; }

protected:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  NodeView *mSource, *mDestination;

  QPointF sourcePoint;
  QPointF destPoint;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeConnectionView_H
