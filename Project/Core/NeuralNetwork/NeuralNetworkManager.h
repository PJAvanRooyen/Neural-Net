#ifndef NeuralNetworkManager_H
#define NeuralNetworkManager_H

#include "Shared/NodeNetwork/NodeNetworkManager.h"

#include <optional>

// test
#include "Shared/NeuralNetwork/Defines.h"
// test

namespace Tests {
class NeuralNetTest;
}

namespace Core {
namespace NodeNetwork {

template <typename DataType> class NeuralNetwork;

class NeuralNetworkManager : public Shared::NodeNetwork::NodeNetworkManager {
  Q_OBJECT

  friend class Tests::NeuralNetTest;

public:
  NeuralNetworkManager(QObject *parent = nullptr);

  ~NeuralNetworkManager();

  NeuralNetwork<double> *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes,
                    const double learningRate,
                    const std::optional<unsigned> seed, const QUuid &networkId);

private:
  void customEvent(QEvent *event) override;

  static void
  test(std::vector<std::pair<std::vector<double>, std::vector<double>>>
           learningSet,
       std::vector<std::pair<std::vector<double>, std::vector<double>>>
           testingSet,
       const QUuid &networkId,
       Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
       const double valuePollingRate, const bool debug);

  static bool
  testIteration(std::vector<double> &inputValues,
                std::vector<double> &desiredOutputs, const QUuid &networkId,
                Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                const bool learn, const bool debug);

private:
  static bool
  testIteration(std::vector<double> &inputValues,
                std::vector<double> &desiredOutputs, const QUuid &networkId,
                Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                const bool learn, const bool debug,
                Shared::NodeNetwork::NeuralNetworkData<double> &result);
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkManager_H
