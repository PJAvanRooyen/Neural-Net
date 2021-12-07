#include "NodeNetwork.h"
#include "NodeNetworkView.h"

namespace UI {
namespace NodeNetwork {

NodeNetwork::NodeNetwork(QObject *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeNetwork() {}

QGraphicsItem *NodeNetwork::createView(QGraphicsItem *parentView) {
  return new NodeNetworkView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
