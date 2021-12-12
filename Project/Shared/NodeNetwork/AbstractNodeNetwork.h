#ifndef AbstractNodeNetwork_H
#define AbstractNodeNetwork_H

#include "AbstractNode.h"

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
public:
  AbstractNodeNetwork();

  ~AbstractNodeNetwork();

  std::vector<AbstractNodeNetworkLayer *> layers() const;

  std::vector<AbstractNodeConnection *>
  layerInputConnections(const unsigned long layerIndex) const;

  std::vector<AbstractNodeConnection *>
  layerOutputConnections(const unsigned long layerIndex) const;

  virtual void addLayer(AbstractNodeNetworkLayer *layer);

  virtual void addLayers(std::vector<AbstractNodeNetworkLayer *> &layers);

protected:
  std::vector<AbstractNodeNetworkLayer *> mLayers;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeNetwork_H
