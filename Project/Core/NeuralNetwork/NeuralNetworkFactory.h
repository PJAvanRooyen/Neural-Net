#ifndef NeuralNetworkFactory_H
#define NeuralNetworkFactory_H

#include "NeuralNetwork.h"
#include "Shared/NodeNetwork/NodeNetworkFactory.h"

namespace Core {
namespace NodeNetwork {

class NeuralNetworkFactory : public Shared::NodeNetwork::NodeNetworkFactory {
public:
  NeuralNetworkFactory();

  ~NeuralNetworkFactory();

  template <class DataType>
  static NeuralNetwork<DataType> *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes,
                    const double learningRate, std::optional<unsigned> seed) {
    gLearningRate = learningRate;
    sRandomizer.seed(seed.has_value() ? seed.value() : std::time(0));

    auto *neuralNetwork = new NeuralNetwork<DataType>();
    Shared::NodeNetwork::NodeNetworkFactory::buildMeshNetwork(neuralNetwork,
                                                              layerSizes);

    // how a neuron is initialized depends on its connections, therefore it must
    // wait until it receives all its connections before getting initialized.
    const auto &layers = neuralNetwork->layers();
    for (const auto *layer : layers) {
      const auto &nodes = layer->nodes();
      for (auto *node : nodes) {
        static_cast<Neuron<DataType> *>(node)->init();
      }
    }

    return neuralNetwork;
  }
};

} // namespace NodeNetwork
} // namespace Core

#endif // NeuralNetworkFactory_H
