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

  static_cast<NodeNetworkView *>(view())->addLayer(
      static_cast<NodeNetworkLayerView *>(
          static_cast<NodeNetworkLayer *>(layer)->view()));
}

void NodeNetwork::addLayers(
    std::vector<Shared::NodeNetwork::AbstractNodeNetworkLayer *> &layers) {
  AbstractNodeNetwork::addLayers(layers);

  for (auto *layer : layers) {
    static_cast<NodeNetworkView *>(view())->addLayer(
        static_cast<NodeNetworkLayerView *>(
            static_cast<NodeNetworkLayer *>(layer)->view()));
  }
}

QGraphicsItem *NodeNetwork::createView(QGraphicsItem *parentView) {
  return new NodeNetworkView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
