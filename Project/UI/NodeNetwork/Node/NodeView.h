#ifndef NodeView_H
#define NodeView_H

#include <QGraphicsEllipseItem>

namespace UI {
namespace Node {

class NodeConnectionView;

class NodeView : public QGraphicsItem {
public:
  NodeView(QGraphicsItem *parent = Q_NULLPTR);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void addNodeConnection(NodeConnectionView *nodeConnection);
  QVector<NodeConnectionView *> nodeConnections() const;

protected:
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
  QVector<NodeConnectionView *> mNodeConnections;
};

} // namespace Node
} // namespace UI
#endif // NodeView_H
