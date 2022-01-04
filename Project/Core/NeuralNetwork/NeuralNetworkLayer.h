#ifndef NeuralNetworkLayer_H
#define NeuralNetworkLayer_H

#include "Core/NodeNetwork/NodeNetworkLayer.h"

namespace Core {
namespace NodeNetwork {

template <typename DataType> class Neuron;

template <typename DataType>
class NeuralNetworkLayer : public Core::NodeNetwork::NodeNetworkLayer {
public:
  NeuralNetworkLayer() {}

  ~NeuralNetworkLayer() {}

  const std::vector<Neuron<DataType> *> &neurons() const {
    return reinterpret_cast<const std::vector<Neuron<DataType> *> &>(
        NodeNetworkLayer::nodes());
  }
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkLayer_H
