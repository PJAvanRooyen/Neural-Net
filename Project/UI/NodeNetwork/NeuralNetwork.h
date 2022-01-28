#ifndef NeuralNetworkController_H
#define NeuralNetworkController_H

#include "Shared/NeuralNetwork/Defines.h"
#include "UI/NodeNetwork/NodeNetwork.h"

namespace UI {
namespace NodeNetwork {

class NeuralNetworkLayer;

class NeuralNetwork : public UI::NodeNetwork::NodeNetwork {
public:
  NeuralNetwork(QObject *parent = Q_NULLPTR);

  Shared::NodeNetwork::AbstractNodeNetworkLayer *addLayer() override;

  Shared::NodeNetwork::AbstractNodeConnection *
  addConnection(AbstractNode *sourceNode,
                AbstractNode *destinationNode) override;

  void
  setData(const Shared::NodeNetwork::NeuralNetworkData<double> &neuralNetData);
};

} // namespace NodeNetwork
} // namespace UI

#endif // NeuralNetworkController_H
