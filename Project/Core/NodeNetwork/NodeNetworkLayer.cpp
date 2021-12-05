#include "NodeNetworkLayer.h"

namespace Core {
namespace NodeNetwork {

NodeNetworkLayer::NodeNetworkLayer() {}

NodeNetworkLayer::~NodeNetworkLayer() {}

std::vector<Node *> NodeNetworkLayer::nodes() const { return mNodes; }
} // namespace NodeNetwork
} // namespace Core
