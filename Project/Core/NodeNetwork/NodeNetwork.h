#ifndef NodeNetwork_H
#define NodeNetwork_H

#include "Node.h"
#include "NodeNetworkLayer.h"

namespace Core {
namespace NodeNetwork {

/*
 * A node network can also be a node in a larger node network.
 * A node network has input and output connections, which are the start and end
 * of the network. It further has node network layers between those connections.
 */
class NodeNetwork : public Node {
public:
  NodeNetwork();

  ~NodeNetwork();

  std::vector<NodeNetworkLayer *> layers() const;

  std::vector<NodeConnection *>
  layerInputConnections(const unsigned long layerIndex) const;

  std::vector<NodeConnection *>
  layerOutputConnections(const unsigned long layerIndex) const;

  void addLayer(NodeNetworkLayer *layer,
                std::vector<NodeConnection *> connectionsToPreviousLayer);

  void addOutputLayerConnections(
      std::vector<NodeConnection *> outputLayerConnections);

private:
  std::vector<NodeNetworkLayer *> mLayers;

  std::vector<std::vector<NodeConnection *>> mLayerConnections;
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetwork_H
