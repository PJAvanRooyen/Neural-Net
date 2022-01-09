#ifndef NodeView_H
#define NodeView_H

#include "Shared/NodeNetwork/AbstractNode.h"

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

class NodeConnectionView;

class NodeView : public QGraphicsItem,
                 public Shared::NodeNetwork::AbstractNode {
public:
  NodeView(QGraphicsItem *parent = Q_NULLPTR);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

protected:
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NodeView_H
