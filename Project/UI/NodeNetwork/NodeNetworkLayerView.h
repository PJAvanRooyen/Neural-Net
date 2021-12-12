#ifndef NodeNetworkLayerView_H
#define NodeNetworkLayerView_H

#include "Shared/NodeNetwork/AbstractNodeNetworkLayer.h"

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

class NodeView;

class NodeNetworkLayerView
    : public QGraphicsItem,
      public Shared::NodeNetwork::AbstractNodeNetworkLayer {
  static const qreal kBorder;
  static const qreal kNodeOffset;

public:
  NodeNetworkLayerView(QGraphicsItem *parent = Q_NULLPTR);

protected:
  void repositionNodes();

  // AbstractNodeNetworkLayer interface
public:
  void addNode(Shared::NodeNetwork::AbstractNode *node);
  void addNodes(std::vector<Shared::NodeNetwork::AbstractNode *> &nodes);

  // QGraphicsItem interface
public:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkLayerController_H
