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
public:
  NodeNetworkLayerView(QGraphicsItem *parent = Q_NULLPTR);

  QRectF boundingRect() const;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkLayerController_H
