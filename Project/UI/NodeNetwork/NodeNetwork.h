#ifndef NodeNetworkController_H
#define NodeNetworkController_H

#include "Shared/NodeNetwork/AbstractNodeNetwork.h"
#include "UI/NodeNetwork/NodeConnection.h"
#include "UI/ViewController/AbstractViewController.h"

namespace UI {
namespace NodeNetwork {

class NodeNetworkLayer;

/*
 * A node network can also be a node in a larger node network.
 * A node network has input and output connections, which are the start and end
 * of the network. It further has node network layers between those connections.
 */
class NodeNetwork : public AbstractGraphicsItemController,
                    public Shared::NodeNetwork::AbstractNodeNetwork {
public:
  NodeNetwork(QObject *parent = Q_NULLPTR);

  virtual Shared::NodeNetwork::AbstractNodeNetworkLayer *addLayer() override;

  void addLayer(NodeNetworkLayer *layer);

  void addLayers(std::vector<Shared::NodeNetwork::AbstractNodeNetworkLayer *>
                     &layers) override;

  virtual Shared::NodeNetwork::AbstractNodeConnection *
  addConnection(AbstractNode *sourceNode,
                AbstractNode *destinationNode) override;

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkController_H
