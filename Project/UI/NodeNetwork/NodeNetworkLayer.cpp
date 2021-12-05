#include "NodeNetworkLayer.h"

namespace UI {
namespace NodeNetwork {

NodeNetworkLayer::NodeNetworkLayer() {}

NodeNetworkLayer::~NodeNetworkLayer() {}

QVector<Node *> NodeNetworkLayer::nodes() const { return mNodes; }
} // namespace NodeNetwork
} // namespace UI
