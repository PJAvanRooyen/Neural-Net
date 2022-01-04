#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Core/NodeNetwork/NodeNetwork.h"

namespace Core {
namespace NodeNetwork {

template <typename DataType> class NeuralNetworkLayer;

template <typename DataType> class NeuralNetwork : public NodeNetwork {

public:
  NeuralNetwork() {}

  ~NeuralNetwork() {}

  const NeuralNetworkLayer<DataType> *
  layer(const unsigned long long layerIdx) const {
    return static_cast<const NeuralNetworkLayer<DataType> *>(
        NodeNetwork::layer(layerIdx));
  }

  const std::vector<NeuralNetworkLayer<DataType> *> &layers() const {
    return reinterpret_cast<
        const std::vector<NeuralNetworkLayer<DataType> *> &>(
        NodeNetwork::layers());
  }
};
} // namespace NodeNetwork
} // namespace Core
#endif // NeuralNetwork_H
