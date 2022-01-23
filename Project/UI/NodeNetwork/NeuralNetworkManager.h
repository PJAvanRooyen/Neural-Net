#ifndef NeuralNetworkManagerUI_H
#define NeuralNetworkManagerUI_H

#include "Shared/Communicator/Communicator.h"
#include "Shared/NodeNetwork/NodeNetworkManager.h"

namespace UI {
namespace NodeNetwork {

class NeuralNetworkManager : public Shared::NodeNetwork::NodeNetworkManager {
  Q_OBJECT

public:
  NeuralNetworkManager(QObject *parent = nullptr);

  ~NeuralNetworkManager();

  template <class DerivedNetwork>
  DerivedNetwork *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes) {
    auto *nodeNetwork =
        Shared::NodeNetwork::NodeNetworkManager::createMeshNetwork<
            DerivedNetwork>(layerSizes);

    if (!nodeNetwork) {
      return nullptr;
    }

    auto &communicator = Shared::Communicator::Communicator::instance();
    communicator.postEvent(new Shared::Communicator::EvNeuralNetCreate(
        layerSizes, mNetworks.key(nodeNetwork)));

    return nodeNetwork;
  }

private:
  void customEvent(QEvent *event) override;
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace UI

#endif // NeuralNetworkManagerUI_H
