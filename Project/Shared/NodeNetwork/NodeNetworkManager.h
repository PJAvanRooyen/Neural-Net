#ifndef NodeNetworkManager_H
#define NodeNetworkManager_H

#include "NodeNetworkFactory.h"

#include <QMap>
#include <QObject>
#include <QUuid>

namespace Shared {
namespace NodeNetwork {

class NodeNetworkManager : public QObject {
  Q_OBJECT

public:
  NodeNetworkManager(QObject *parent = nullptr);

  ~NodeNetworkManager();

  QUuid buildMeshNetwork(Shared::NodeNetwork::AbstractNodeNetwork *nodeNetwork,
                         const std::vector<unsigned long> &layerSizes);

  template <class DerivedNetwork>
  QUuid createMeshNetwork(const std::vector<unsigned long> &layerSizes) {
    auto *nodeNetwork =
        Shared::NodeNetwork::NodeNetworkFactory::createMeshNetwork<
            DerivedNetwork>(layerSizes);

    const QUuid networkId = QUuid::createUuid();
    mNetworks.insert(networkId, nodeNetwork);

    return networkId;
  }

  template <class DerivedNetwork>
  DerivedNetwork *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes,
                    const QUuid &networkId) {
    auto *nodeNetwork =
        Shared::NodeNetwork::NodeNetworkFactory::createMeshNetwork<
            DerivedNetwork>(layerSizes);

    mNetworks.insert(networkId, nodeNetwork);

    return nodeNetwork;
  }

  void addNetwork(const QUuid &networkId, AbstractNodeNetwork *nodeNetwork);

  template <class DerivedNetwork>
  DerivedNetwork &network(const QUuid networkId) {
    return static_cast<DerivedNetwork &>(*mNetworks[networkId]);
  }

protected:
  QMap<QUuid, AbstractNodeNetwork *> mNetworks;
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace Shared

#endif // NodeNetworkManager_H
