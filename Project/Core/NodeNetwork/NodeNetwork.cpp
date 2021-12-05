#include "NodeNetwork.h"

namespace Core {
namespace NodeNetwork {

NodeNetwork::NodeNetwork() {}

NodeNetwork::~NodeNetwork() {}

std::vector<NodeNetworkLayer *> NodeNetwork::layers() const { return mLayers; }

std::vector<NodeConnection *>
NodeNetwork::layerInputConnections(const unsigned long layerIndex) const {
  if (layerIndex == 0) {
    return mInputNodeConnections;
  }
  return mLayerConnections[layerIndex - 1];
}

std::vector<NodeConnection *>
NodeNetwork::layerOutputConnections(const unsigned long layerIndex) const {
  if (layerIndex == mLayers.size()) {
    return mOutputNodeConnections;
  }
  return mLayerConnections[layerIndex];
}

void NodeNetwork::addLayer(
    NodeNetworkLayer *layer,
    std::vector<NodeConnection *> connectionsToPreviousLayer) {

  const int layersCount = mLayers.size();
  if (layersCount == 0) {
    mInputNodeConnections.insert(mInputNodeConnections.end(),
                                 connectionsToPreviousLayer.begin(),
                                 connectionsToPreviousLayer.end());
  } else {
    mLayerConnections.insert(mLayerConnections.end(),
                             connectionsToPreviousLayer);
  }

  mLayers.push_back(layer);
}

void NodeNetwork::addOutputLayerConnections(
    std::vector<NodeConnection *> outputLayerConnections) {
  mOutputNodeConnections.insert(mOutputNodeConnections.end(),
                                outputLayerConnections.begin(),
                                outputLayerConnections.end());
}

} // namespace NodeNetwork
} // namespace Core
