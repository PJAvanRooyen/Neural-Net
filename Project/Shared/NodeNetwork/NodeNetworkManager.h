#ifndef NodeNetworkManager_H
#define NodeNetworkManager_H

#include "NodeNetworkFactory.h"

#include <QMap>
#include <QObject>
#include <QUuid>

#include <memory>
#include <optional>
#include <unordered_map>

namespace Shared {
namespace NodeNetwork {

class NodeNetworkManager : public QObject {
  Q_OBJECT

public:
  NodeNetworkManager(QObject *parent = nullptr);

  ~NodeNetworkManager();

  template <class DerivedNetwork>
  DerivedNetwork *
  createMeshNetwork(const std::vector<unsigned long> &layerSizes) {
    auto *nodeNetwork =
        Shared::NodeNetwork::NodeNetworkFactory::createMeshNetwork<
            DerivedNetwork>(layerSizes);

    mNetworks.insert(QUuid::createUuid(), nodeNetwork);

    return nodeNetwork;
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

  template <class DerivedNetwork>
  DerivedNetwork &networkAt(const QUuid networkId) {
    return static_cast<DerivedNetwork &>(*mNetworks[networkId]);
  }

protected:
  QMap<QUuid, AbstractNodeNetwork *> mNetworks;
}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace Shared

#endif // NodeNetworkManager_H
