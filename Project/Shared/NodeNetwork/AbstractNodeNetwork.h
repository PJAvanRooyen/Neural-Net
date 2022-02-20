#ifndef AbstractNodeNetwork_H
#define AbstractNodeNetwork_H

#include "AbstractNode.h"

#include <map>
#include <vector>

namespace Shared {
namespace NodeNetwork {

class AbstractNodeConnection;
class AbstractNodeNetworkLayer;
/*
 * A node network can also be a node in a larger node network.
 * A node network has input and output connections, which are the start and end
 * of the network. It further has node network layers between those connections.
 */
class AbstractNodeNetwork : public AbstractNode {
  friend class AbstractNodeNetworkFactory;

public:
  ~AbstractNodeNetwork();

  const AbstractNodeNetworkLayer *layerAt(const unsigned long layerIndex) const;

  const AbstractNodeNetworkLayer *inputLayer() const;

  const AbstractNodeNetworkLayer *outputLayer() const;

  const std::vector<AbstractNodeNetworkLayer *> &layers() const;

  const std::vector<AbstractNodeConnection *> &
  layerInputConnections(const unsigned long layerIndex) const;

  const std::vector<AbstractNodeConnection *> &
  layerOutputConnections(const unsigned long layerIndex) const;

  virtual Shared::NodeNetwork::AbstractNodeNetworkLayer *addLayer() = 0;

  virtual void addLayer(AbstractNodeNetworkLayer *layer);

  virtual void addLayers(std::vector<AbstractNodeNetworkLayer *> &layers);

  virtual AbstractNodeConnection *
  addConnection(AbstractNode *sourceNode, AbstractNode *destinationNode) = 0;

  unsigned long layerCount() const;

protected:
  AbstractNodeNetwork();

  std::vector<AbstractNodeNetworkLayer *> mLayers;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeNetwork_H
