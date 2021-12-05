#include "NodeNetwork.h"

namespace UI {
namespace NodeNetwork {

NodeNetwork::NodeNetwork() {}

NodeNetwork::~NodeNetwork() {}

QVector<NodeNetworkLayer *> NodeNetwork::layers() const { return mLayers; }

QVector<NodeConnection *>
NodeNetwork::layerInputConnections(const unsigned long layerIndex) const {
  if (layerIndex == 0) {
    return mInputNodeConnections;
  }
  return mLayerConnections[layerIndex - 1];
}

QVector<NodeConnection *>
NodeNetwork::layerOutputConnections(const int layerIndex) const {
  if (layerIndex == mLayers.size()) {
    return mOutputNodeConnections;
  }
  return mLayerConnections[layerIndex];
}

void NodeNetwork::addLayer(
    NodeNetworkLayer *layer,
    QVector<NodeConnection *> connectionsToPreviousLayer) {

  const int layersCount = mLayers.size();
  if (layersCount == 0) {
    mInputNodeConnections.append(connectionsToPreviousLayer);
  } else {
    mLayerConnections.append(connectionsToPreviousLayer);
  }

  mLayers.push_back(layer);
}

void NodeNetwork::addOutputLayerConnections(
    QVector<NodeConnection *> outputLayerConnections) {
  mOutputNodeConnections.append(outputLayerConnections);
}

} // namespace NodeNetwork
} // namespace UI
