#ifndef NodeNetworkFactory_H
#define NodeNetworkFactory_H

#include "AbstractNodeNetwork.h"
#include "AbstractNodeNetworkLayer.h"

#include <vector>

namespace Shared {
namespace NodeNetwork {

class AbstractNodeNetwork;
class AbstractNodeNetworkLayer;
class AbstractNode;
class AbstractNodeConnection;

class NodeNetworkFactory {
public:
  NodeNetworkFactory();

  ~NodeNetworkFactory();

  template <class DerivedNetwork>
  AbstractNodeNetwork *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes) {
    AbstractNodeNetwork *nodeNetwork = new DerivedNetwork();

    for (unsigned long long layerIdx = 0; layerIdx < layerSizes.size();
         ++layerIdx) {
      const unsigned long nodeCount = layerSizes[layerIdx];
      AbstractNodeNetworkLayer *layer = nodeNetwork->addLayer();

      for (unsigned long nodeIdx = 0; nodeIdx < nodeCount; ++nodeIdx) {
        layer->addNode();
      }

      if (layerIdx != 0) {
        const auto &layers = nodeNetwork->layers();

        // connect each current node to each node from the previous layer.
        for (AbstractNode *node : layer->nodes()) {
          const auto &prevLayer = layers[layerIdx - 1];

          for (AbstractNode *prevLayerNode : prevLayer->nodes()) {
            nodeNetwork->addConnection(prevLayerNode, node);
          }
        }
      }
    }

    return nodeNetwork;
  }
};

} // namespace NodeNetwork
} // namespace Shared

#endif // NodeNetworkFactory_H
