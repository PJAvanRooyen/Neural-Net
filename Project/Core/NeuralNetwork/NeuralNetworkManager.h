#ifndef NeuralNetworkManager_H
#define NeuralNetworkManager_H

#include "Shared/NodeNetwork/NodeNetworkManager.h"

namespace Core {
namespace NodeNetwork {

template <typename DataType> class NeuralNetwork;

class NeuralNetworkManager : public Shared::NodeNetwork::NodeNetworkManager {
  Q_OBJECT

public:
  NeuralNetworkManager(QObject *parent = nullptr);

  ~NeuralNetworkManager();

  NeuralNetwork<double> *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes,
                    const double learningRate,
                    const std::optional<unsigned> seed, const QUuid &networkId);

private:
  void customEvent(QEvent *event) override;

  void test(std::vector<std::pair<std::vector<double>, std::vector<double>>>
                learningSet,
            std::vector<std::pair<std::vector<double>, std::vector<double>>>
                testingSet,
            Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
            const double valuePollingRate, const bool debug);
  bool testIteration(std::vector<double> &inputValues,
                     std::vector<double> &desiredOutputs,
                     Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                     const bool learn, const bool debug);
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkManager_H
