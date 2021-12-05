#ifndef NodeNetworkUI_H
#define NodeNetworkUI_H

#include "Node.h"
#include "NodeConnection.h"
#include "NodeNetworkLayer.h"

namespace UI {
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

  QVector<NodeNetworkLayer *> layers() const;

  QVector<NodeConnection *>
  layerInputConnections(const unsigned long layerIndex) const;

  QVector<NodeConnection *> layerOutputConnections(const int layerIndex) const;

  void addLayer(NodeNetworkLayer *layer,
                QVector<NodeConnection *> connectionsToPreviousLayer);

  void
  addOutputLayerConnections(QVector<NodeConnection *> outputLayerConnections);

private:
  QVector<NodeNetworkLayer *> mLayers;

  QVector<QVector<NodeConnection *>> mLayerConnections;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkUI_H
