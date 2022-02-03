#ifndef NeuralNetworkDefines_H
#define NeuralNetworkDefines_H

#include <optional>
#include <vector>

namespace Shared {
namespace NodeNetwork {

template <typename DataType> struct NeuronData {
  std::optional<DataType> bias;

  std::optional<DataType> activation;

  std::optional<DataType> sensitivity;

  std::optional<DataType> desiredActivation;
};

template <typename DataType> struct NeuronConnectionData {
  DataType weight;

  std::optional<DataType> activation;
};

template <typename DataType>
using NeuralNetworkLayerData =
    std::vector<std::pair<NeuronData<DataType>,
                          std::vector<NeuronConnectionData<DataType>>>>;

template <typename DataType>
using NeuralNetworkData = std::vector<NeuralNetworkLayerData<DataType>>;

struct TestConfiguration {
  ulong learningIterations;
  ulong testingIterations;
  std::optional<ulong> weightsAndBiasSeed;
  std::optional<ulong> dataSeed;
  double learningRate;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // NeuralNetworkDefines_H
