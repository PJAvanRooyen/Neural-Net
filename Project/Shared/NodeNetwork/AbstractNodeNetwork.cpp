#include "AbstractNodeNetwork.h"
#include "AbstractNodeNetworkLayer.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeNetwork::AbstractNodeNetwork() : AbstractNode() {}

AbstractNodeNetwork::~AbstractNodeNetwork() {}

std::vector<AbstractNodeNetworkLayer *> AbstractNodeNetwork::layers() const {
  return mLayers;
}

std::vector<AbstractNodeConnection *>
AbstractNodeNetwork::layerInputConnections(
    const unsigned long layerIndex) const {
  if (layerIndex < mLayers.size() - 1) {
    return {};
  } else {
    return mLayers[layerIndex]->inputNodeConnections();
  }
}

std::vector<AbstractNodeConnection *>
AbstractNodeNetwork::layerOutputConnections(
    const unsigned long layerIndex) const {
  if (layerIndex < mLayers.size() - 1) {
    return {};
  } else {
    return mLayers[layerIndex]->inputNodeConnections();
  }
}

void AbstractNodeNetwork::addLayer(AbstractNodeNetworkLayer *layer) {

  const int layersCount = mLayers.size();

  if (layersCount == 0) {
    const auto &layerInputConnections = layer->inputNodeConnections();

    mInputNodeConnections = layerInputConnections;
  }

  mOutputNodeConnections = layer->outputNodeConnections();

  mLayers.push_back(layer);
}

void AbstractNodeNetwork::addLayers(
    std::vector<AbstractNodeNetworkLayer *> &layers) {
  const int layersToAddCount = layers.size();
  if (layersToAddCount == 0) {
    return;
  }

  const int existingLayersCount = mLayers.size();
  if (existingLayersCount == 0) {
    mInputNodeConnections = (*layers.begin())->inputNodeConnections();
  }
  mOutputNodeConnections = (*(--layers.end()))->outputNodeConnections();

  mLayers.insert(mLayers.end(), layers.begin(), layers.end());
}

} // namespace NodeNetwork
} // namespace Shared
