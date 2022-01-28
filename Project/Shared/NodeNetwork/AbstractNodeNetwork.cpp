#include "AbstractNodeNetwork.h"
#include "AbstractNodeConnection.h"
#include "AbstractNodeNetworkLayer.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeNetwork::AbstractNodeNetwork() : AbstractNode() {}

AbstractNodeNetwork::~AbstractNodeNetwork() {}

const AbstractNodeNetworkLayer *
AbstractNodeNetwork::layerAt(const unsigned long layerIndex) const {
  if (layerIndex > mLayers.size() - 1) {
    return nullptr;
  } else {
    return mLayers[layerIndex];
  }
}

const AbstractNodeNetworkLayer *AbstractNodeNetwork::inputLayer() const {
  if (mLayers.size() == 0) {
    return nullptr;
  } else {
    return mLayers[0];
  }
}

const AbstractNodeNetworkLayer *AbstractNodeNetwork::outputLayer() const {
  if (mLayers.size() == 0) {
    return nullptr;
  } else {
    return mLayers[layerCount() - 1];
  }
}

const std::vector<AbstractNodeNetworkLayer *> &
AbstractNodeNetwork::layers() const {
  return mLayers;
}

const std::vector<AbstractNodeConnection *> &
AbstractNodeNetwork::layerInputConnections(
    const unsigned long layerIndex) const {
  static const std::vector<AbstractNodeConnection *> kEmpty = {};

  if (layerIndex > mLayers.size() - 1) {
    return kEmpty;
  } else {
    return mLayers[layerIndex]->inputNodeConnections();
  }
}

const std::vector<AbstractNodeConnection *> &
AbstractNodeNetwork::layerOutputConnections(
    const unsigned long layerIndex) const {
  static const std::vector<AbstractNodeConnection *> kEmpty = {};

  if (layerIndex > mLayers.size() - 1) {
    return kEmpty;
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

unsigned long AbstractNodeNetwork::layerCount() const { return mLayers.size(); }

} // namespace NodeNetwork
} // namespace Shared
