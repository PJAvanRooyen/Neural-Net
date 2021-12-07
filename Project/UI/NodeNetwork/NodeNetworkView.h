#ifndef NodeNetworkView_H
#define NodeNetworkView_H

#include "Shared/NodeNetwork/AbstractNodeNetwork.h"

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

/*
 * A node network can also be a node in a larger node network.
 * A node network has input and output connections, which are the start and end
 * of the network. It further has node network layers between those connections.
 */
class NodeNetworkView : public QGraphicsItem,
                        public Shared::NodeNetwork::AbstractNodeNetwork {
public:
  NodeNetworkView(QGraphicsItem *parent = Q_NULLPTR);

  QRectF boundingRect() const;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkView_H