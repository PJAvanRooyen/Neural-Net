#include "AbstractNodeNetwork.h"
#include "AbstractNodeConnection.h"
#include "AbstractNodeNetworkLayer.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeNetwork::AbstractNodeNetwork() : AbstractNode() {}

AbstractNodeNetwork::~AbstractNodeNetwork() {}

const AbstractNodeNetworkLayer *
AbstractNodeNetwork::layer(const unsigned long long layerIdx) const {
  return mLayers[layerIdx];
}

const std::vector<AbstractNodeNetworkLayer *> &
AbstractNodeNetwork::layers() const {
  return mLayers;
}

const std::vector<AbstractNodeConnection *> &
AbstractNodeNetwork::layerInputConnections(
    const unsigned long long layerIndex) const {
  static const std::vector<AbstractNodeConnection *> kEmpty = {};

  if (layerIndex < mLayers.size() - 1) {
    return kEmpty;
  } else {
    return mLayers[layerIndex]->inputNodeConnections();
  }
}

const std::vector<AbstractNodeConnection *> &
AbstractNodeNetwork::layerOutputConnections(
    const unsigned long long layerIndex) const {
  static const std::vector<AbstractNodeConnection *> kEmpty = {};

  if (layerIndex < mLayers.size() - 1) {
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

void AbstractNodeNetwork::addConnection(AbstractNodeConnection *connection) {

  auto *connectionSourceNode = connection->sourceNode();
  auto nodeIt = mNodeOutputConnections.find(connectionSourceNode);
  if (nodeIt != mNodeOutputConnections.end()) {
    mNodeOutputConnections[connectionSourceNode].push_back(connection);
  } else {
    std::vector<AbstractNodeConnection *> nodeConnections = {connection};
    mNodeOutputConnections.insert(
        std::make_pair(connectionSourceNode, nodeConnections));
  }
}

unsigned long long AbstractNodeNetwork::layerCount() const {
  return mLayers.size();
}

} // namespace NodeNetwork
} // namespace Shared
