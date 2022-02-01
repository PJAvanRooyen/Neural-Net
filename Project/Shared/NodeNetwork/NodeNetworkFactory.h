#ifndef NodeNetworkFactory_H
#define NodeNetworkFactory_H

#include "AbstractNodeNetwork.h"
#include "AbstractNodeNetworkLayer.h"

#include <memory>
#include <vector>

namespace Shared {
namespace NodeNetwork {

class NodeNetworkFactory {
public:
  NodeNetworkFactory();

  ~NodeNetworkFactory();

  static bool buildMeshNetwork(AbstractNodeNetwork *nodeNetwork,
                               const std::vector<unsigned long> &layerSizes) {
    for (unsigned long layerIdx = 0; layerIdx < layerSizes.size(); ++layerIdx) {
      const unsigned long nodeCount = layerSizes[layerIdx];
      AbstractNodeNetworkLayer *layer = nodeNetwork->addLayer();

      for (unsigned long nodeIdx = 0; nodeIdx < nodeCount; ++nodeIdx) {
        layer->addNode();
      }

      if (layerIdx != 0) {
        const auto &layers = nodeNetwork->layers();

        // connect each current node to each node from the previous layer.
        for (AbstractNode *node : layer->nodes()) {
          AbstractNodeNetworkLayer *prevLayer = layers[layerIdx - 1];

          for (AbstractNode *prevLayerNode : prevLayer->nodes()) {
            nodeNetwork->addConnection(prevLayerNode, node);
          }
        }
      }
    }

    return true;
  }

  template <class DerivedNetwork>
  static DerivedNetwork *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes) {
    auto *nodeNetwork = new DerivedNetwork();

    buildMeshNetwork(nodeNetwork, layerSizes);

    return nodeNetwork;
  }
};

} // namespace NodeNetwork
} // namespace Shared

#endif // NodeNetworkFactory_H
