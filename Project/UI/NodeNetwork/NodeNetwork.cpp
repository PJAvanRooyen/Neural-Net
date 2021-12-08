#include "NodeNetwork.h"
#include "NodeNetworkLayer.h"
#include "NodeNetworkLayerView.h"
#include "NodeNetworkView.h"

namespace UI {
namespace NodeNetwork {

NodeNetwork::NodeNetwork(QObject *parent)
    : AbstractGraphicsItemController(parent),
      Shared::NodeNetwork::AbstractNodeNetwork() {}

void NodeNetwork::addLayer(
    Shared::NodeNetwork::AbstractNodeNetworkLayer *layer) {
  AbstractNodeNetwork::addLayer(layer);

  view<NodeNetworkView>()->addLayer(
      static_cast<NodeNetworkLayer *>(layer)->view<NodeNetworkLayerView>());
}

void NodeNetwork::addLayers(
    std::vector<Shared::NodeNetwork::AbstractNodeNetworkLayer *> &layers) {
  AbstractNodeNetwork::addLayers(layers);

  for (auto *layer : layers) {
    view<NodeNetworkView>()->addLayer(
        static_cast<NodeNetworkLayer *>(layer)->view<NodeNetworkLayerView>());
  }
}

QGraphicsItem *NodeNetwork::createViewBase(QGraphicsItem *parentView) {
  return new NodeNetworkView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
