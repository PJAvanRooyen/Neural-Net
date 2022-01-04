#ifndef AbstractNodeNetworkFactory_H
#define AbstractNodeNetworkFactory_H

#include <vector>

namespace Shared {
namespace NodeNetwork {

class AbstractNodeNetwork;
class AbstractNodeNetworkLayer;
class AbstractNode;
class AbstractNodeConnection;

class AbstractNodeNetworkFactory {
public:
  AbstractNodeNetworkFactory();

  ~AbstractNodeNetworkFactory();

  virtual AbstractNodeNetwork *createNodeNetwork() const = 0;

  virtual AbstractNodeNetworkLayer *
  addNodeNetworkLayer(AbstractNodeNetwork *nodeNetwork) const = 0;

  virtual AbstractNode *
  addNode(AbstractNodeNetworkLayer *nodeNetworkLayer) const = 0;

  virtual AbstractNodeConnection *
  addNodeConnection(AbstractNode *sourceNode, AbstractNode *destinationNode,
                    AbstractNodeNetwork *nodeNetwork) const = 0;

  AbstractNodeNetwork *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes);
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeNetworkFactory_H
