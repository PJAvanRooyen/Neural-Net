#ifndef NeuralNetworkManagerUI_H
#define NeuralNetworkManagerUI_H

#include "Shared/Communicator/Communicator.h"
#include "Shared/NodeNetwork/NodeNetworkManager.h"

namespace UI {
namespace NodeNetwork {

class NeuralNetwork;

class NeuralNetworkManager : public Shared::NodeNetwork::NodeNetworkManager {
  Q_OBJECT

public:
  NeuralNetworkManager(QObject *parent = nullptr);

  ~NeuralNetworkManager();

  QUuid createMeshNetwork(const std::vector<unsigned long> &layerSizes,
                          const double learningRate,
                          const std::optional<unsigned> seed);

  void runTest(const QUuid &networkId);

private:
  void customEvent(QEvent *event) override;
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace UI

#endif // NeuralNetworkManagerUI_H
