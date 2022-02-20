#ifndef NeuralNetworkManager_H
#define NeuralNetworkManager_H

#include "Shared/NodeNetwork/NodeNetworkManager.h"

#include <optional>

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
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkManager_H
