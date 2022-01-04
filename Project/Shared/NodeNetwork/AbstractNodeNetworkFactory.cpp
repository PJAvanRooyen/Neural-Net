#include "AbstractNodeNetworkFactory.h"
#include "AbstractNodeNetwork.h"
#include "AbstractNodeNetworkLayer.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeNetworkFactory::AbstractNodeNetworkFactory() {}

AbstractNodeNetworkFactory::~AbstractNodeNetworkFactory() {}

AbstractNodeNetwork *AbstractNodeNetworkFactory::createMeshNetwork(
    const std::vector<unsigned long> &layerSizes) {
  AbstractNodeNetwork *nodeNetwork = createNodeNetwork();

  for (unsigned long long layerIdx = 0; layerIdx < layerSizes.size();
       ++layerIdx) {
    const unsigned long nodeCount = layerSizes[layerIdx];
    AbstractNodeNetworkLayer *layer = addNodeNetworkLayer(nodeNetwork);

    for (unsigned long nodeIdx = 0; nodeIdx < nodeCount; ++nodeIdx) {
      addNode(layer);
    }

    if (layerIdx != 0) {
      const auto &layers = nodeNetwork->layers();

      // connect each current node to each node from the previous layer.
      for (AbstractNode *node : layer->nodes()) {
        const auto &prevLayer = layers[layerIdx - 1];

        for (AbstractNode *prevLayerNode : prevLayer->nodes()) {
          addNodeConnection(prevLayerNode, node, nodeNetwork);
        }
      }
    }
  }

  return nodeNetwork;
}

} // namespace NodeNetwork
} // namespace Shared
