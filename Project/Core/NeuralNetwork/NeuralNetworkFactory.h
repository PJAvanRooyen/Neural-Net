#ifndef NeuralNetworkFactory_H
#define NeuralNetworkFactory_H

#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkLayer.h"
#include "Core/NeuralNetwork/Neuron.h"
#include "Shared/NodeNetwork/AbstractNodeNetworkFactory.h"

namespace Shared::NodeNetwork {
class AbstractNodeNetwork;
class AbstractNodeNetworkLayer;
class AbstractNode;
class AbstractNodeConnection;
} // namespace Shared::NodeNetwork

namespace Core {
namespace NodeNetwork {

template <typename DataType>
class NeuralNetworkFactory
    : public Shared::NodeNetwork::AbstractNodeNetworkFactory {

public:
  NeuralNetworkFactory() {}

  ~NeuralNetworkFactory() {}

  Shared::NodeNetwork::AbstractNodeNetwork *createNodeNetwork() const override {
    return new NeuralNetwork<DataType>();
  }

  Shared::NodeNetwork::AbstractNodeNetworkLayer *addNodeNetworkLayer(
      Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork) const override {
    auto *nodeNet = static_cast<NeuralNetwork<DataType> *>(nodeNetwork);
    auto *layer = new NeuralNetworkLayer<DataType>();
    nodeNet->addLayer(layer);
    return layer;
  }

  Shared::NodeNetwork::AbstractNode *
  addNode(Shared::NodeNetwork::AbstractNodeNetworkLayer *nodeNetworkLayer)
      const override {
    auto *nodeNetLayer =
        static_cast<NeuralNetworkLayer<DataType> *>(nodeNetworkLayer);
    auto *neuron = new Neuron<DataType>();
    nodeNetLayer->addNode(neuron);
    return neuron;
  }

  Shared::NodeNetwork::AbstractNodeConnection *addNodeConnection(
      Shared::NodeNetwork::AbstractNode *sourceNode,
      Shared::NodeNetwork::AbstractNode *destinationNode,
      Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork) const override {
    auto *nodeNet = static_cast<NeuralNetwork<DataType> *>(nodeNetwork);
    auto *sourceNeuron = static_cast<Neuron<DataType> *>(sourceNode);
    auto *destinationNeuron = static_cast<Neuron<DataType> *>(destinationNode);

    auto *neuronConnection =
        new NeuronConnection<DataType>(sourceNeuron, destinationNeuron);
    nodeNet->addNodeConnection(neuronConnection);
    return neuronConnection;
  }
};

} // namespace NodeNetwork
} // namespace Core
#endif // NeuralNetworkFactory_H
