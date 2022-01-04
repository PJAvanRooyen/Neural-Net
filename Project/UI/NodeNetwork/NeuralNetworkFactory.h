#ifndef NeuralNetworkFactoryUI_H
#define NeuralNetworkFactoryUI_H

#include "Shared/NodeNetwork/AbstractNodeNetworkFactory.h"

namespace Shared::NodeNetwork {
class AbstractNodeNetwork;
class AbstractNodeNetworkLayer;
class AbstractNode;
class AbstractNodeConnection;
} // namespace Shared::NodeNetwork

namespace UI {
namespace NodeNetwork {

class NeuralNetworkFactory
    : public Shared::NodeNetwork::AbstractNodeNetworkFactory {

public:
  NeuralNetworkFactory();

  ~NeuralNetworkFactory();

  Shared::NodeNetwork::AbstractNodeNetwork *createNodeNetwork() const override;

  Shared::NodeNetwork::AbstractNodeNetworkLayer *addNodeNetworkLayer(
      Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork) const override;

  Shared::NodeNetwork::AbstractNode *
  addNode(Shared::NodeNetwork::AbstractNodeNetworkLayer *nodeNetworkLayer)
      const override;

  Shared::NodeNetwork::AbstractNodeConnection *addNodeConnection(
      Shared::NodeNetwork::AbstractNode *sourceNode,
      Shared::NodeNetwork::AbstractNode *destinationNode,
      Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork) const override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuralNetworkFactoryUI_H
