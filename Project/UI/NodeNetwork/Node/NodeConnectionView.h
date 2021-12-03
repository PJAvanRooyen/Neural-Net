#ifndef NodeConnectionView_H
#define NodeConnectionView_H
#include "NodeView.h"

#include <QGraphicsItem>

namespace UI {
namespace Node {

class NodeConnectionView : public QGraphicsItem {
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
  NodeView *source, *dest;

  QPointF sourcePoint;
  QPointF destPoint;
  qreal arrowSize = 10;
};

} // namespace Node
} // namespace UI

#endif // NodeConnectionView_H
