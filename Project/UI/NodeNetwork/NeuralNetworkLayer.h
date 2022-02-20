#ifndef NeuralNetworkLayerController_H
#define NeuralNetworkLayerController_H

#include "UI/NodeNetwork/NodeNetworkLayer.h"

namespace UI {
namespace NodeNetwork {

class Neuron;

class NeuralNetworkLayer : public UI::NodeNetwork::NodeNetworkLayer {
public:
  NeuralNetworkLayer(QObject *parent = Q_NULLPTR);

  Shared::NodeNetwork::AbstractNode *addNode() override;

  void addNeuron(Neuron *neuron);
};

} // namespace NodeNetwork
} // namespace UI

#endif // NeuralNetworkLayerController_H
