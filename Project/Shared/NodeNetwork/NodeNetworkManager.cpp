#include "NodeNetworkManager.h"

namespace Shared {
namespace NodeNetwork {

NodeNetworkManager::NodeNetworkManager(QObject *parent)
    : QObject(parent), mNetworks() {}

NodeNetworkManager::~NodeNetworkManager() {}

QUuid NodeNetworkManager::buildMeshNetwork(
    AbstractNodeNetwork *nodeNetwork,
    const std::vector<unsigned long> &layerSizes) {

  const bool ok = Shared::NodeNetwork::NodeNetworkFactory::buildMeshNetwork(
      nodeNetwork, layerSizes);

  if (!ok) {
    Q_ASSERT(false);
    return QUuid();
  }

  const QUuid networkId = QUuid::createUuid();
  mNetworks.insert(networkId, nodeNetwork);

  return networkId;
}

void NodeNetworkManager::addNetwork(const QUuid &networkId,
                                    AbstractNodeNetwork *nodeNetwork) {
  mNetworks.insert(networkId, nodeNetwork);
}

} // namespace NodeNetwork
} // namespace Shared
