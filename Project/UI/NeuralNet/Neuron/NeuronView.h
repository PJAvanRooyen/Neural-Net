#ifndef NeuronView_H
#define NeuronView_H

#include <QGraphicsEllipseItem>

namespace UI {
namespace Neuron {

class NeuronView : public QGraphicsItem {
public:
  NeuronView(QGraphicsItem *parent = Q_NULLPTR);

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

} // namespace Neuron
} // namespace UI
#endif // NeuronView_H
