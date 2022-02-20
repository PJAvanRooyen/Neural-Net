#include "AbstractNodeNetworkLayer.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeNetworkLayer::AbstractNodeNetworkLayer() {}

AbstractNodeNetworkLayer::~AbstractNodeNetworkLayer() {}

const std::vector<AbstractNode *> &AbstractNodeNetworkLayer::nodes() const {
  return mNodes;
}

void AbstractNodeNetworkLayer::addNode(AbstractNode *node) {
  const auto &nodeInputConnections = node->inputNodeConnections();
  if (!nodeInputConnections.empty()) {
    mInputNodeConnections.insert(mInputNodeConnections.end(),
                                 nodeInputConnections.begin(),
                                 nodeInputConnections.end());
  }

  const auto &nodeOutputConnections = node->outputNodeConnections();
  if (!nodeOutputConnections.empty()) {
    mOutputNodeConnections.insert(mOutputNodeConnections.end(),
                                  nodeOutputConnections.begin(),
                                  nodeOutputConnections.end());
  }

  mNodes.push_back(node);
}

void AbstractNodeNetworkLayer::addNodes(std::vector<AbstractNode *> &nodes) {
  for (auto *node : nodes) {
    addNode(node);
  }
}

unsigned long AbstractNodeNetworkLayer::size() const { return mNodes.size(); }
} // namespace NodeNetwork
} // namespace Shared
