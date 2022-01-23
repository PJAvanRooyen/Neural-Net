#include "NodeNetworkManager.h"

namespace Shared {
namespace NodeNetwork {

NodeNetworkManager::NodeNetworkManager(QObject *parent)
    : QObject(parent), mNetworks() {}

NodeNetworkManager::~NodeNetworkManager() {}

} // namespace NodeNetwork
} // namespace Shared
