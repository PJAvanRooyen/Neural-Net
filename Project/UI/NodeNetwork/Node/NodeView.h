#ifndef NodeView_H
#define NodeView_H

#include <QGraphicsEllipseItem>

namespace UI {
namespace Node {

class NodeView : public QGraphicsItem {
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

} // namespace Node
} // namespace UI
#endif // NodeView_H
