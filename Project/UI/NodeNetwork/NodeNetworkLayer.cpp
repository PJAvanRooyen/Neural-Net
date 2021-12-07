#include "NodeNetworkLayer.h"
#include "NodeConnection.h"
#include "NodeNetworkLayerView.h"

namespace UI {
namespace NodeNetwork {

NodeNetworkLayer::NodeNetworkLayer(QObject *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeNetworkLayer() {}

QGraphicsItem *NodeNetworkLayer::createView(QGraphicsItem *parentView) {
  return new NodeNetworkLayerView(parentView);
}
} // namespace NodeNetwork
} // namespace UI
