#include "AbstractNodeNetworkLayer.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeNetworkLayer::AbstractNodeNetworkLayer() {}

AbstractNodeNetworkLayer::~AbstractNodeNetworkLayer() {}

const std::vector<AbstractNode *> &AbstractNodeNetworkLayer::nodes() const {
  return mNodes;
}

void AbstractNodeNetworkLayer::addNode(AbstractNode *node) {
  mNodes.push_back(node);
  const auto &nodeInputConnections = node->inputNodeConnections();
  const auto &nodeOutputConnections = node->outputNodeConnections();

  mInputNodeConnections.insert(mInputNodeConnections.end(),
                               nodeInputConnections.begin(),
                               nodeInputConnections.end());
  mOutputNodeConnections.insert(mOutputNodeConnections.end(),
                                nodeOutputConnections.begin(),
                                nodeOutputConnections.end());
}

void AbstractNodeNetworkLayer::addNodes(std::vector<AbstractNode *> &nodes) {
  for (auto *node : nodes) {
    addNode(node);
  }
}
} // namespace NodeNetwork
} // namespace Shared
