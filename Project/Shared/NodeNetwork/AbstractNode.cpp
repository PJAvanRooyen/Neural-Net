#include "AbstractNode.h"

namespace Shared {
namespace NodeNetwork {

AbstractNode::AbstractNode() {}

AbstractNode::~AbstractNode() {}

void AbstractNode::init() {}

void AbstractNode::addInputNodeConnection(
    AbstractNodeConnection *nodeConnection) {
  mInputNodeConnections.push_back(nodeConnection);
}

void AbstractNode::addInputNodeConnections(
    std::vector<AbstractNodeConnection *> &nodeConnections) {
  for (auto *nodeConnection : nodeConnections) {
    addInputNodeConnection(nodeConnection);
  }
}

const std::vector<AbstractNodeConnection *> &
AbstractNode::inputNodeConnections() const {
  return mInputNodeConnections;
}

void AbstractNode::addOutputNodeConnection(
    AbstractNodeConnection *nodeConnection) {
  mOutputNodeConnections.push_back(nodeConnection);
}

void AbstractNode::addOutputNodeConnections(
    std::vector<AbstractNodeConnection *> &nodeConnections) {
  for (auto *nodeConnection : nodeConnections) {
    addOutputNodeConnection(nodeConnection);
  }
}

const std::vector<AbstractNodeConnection *> &
AbstractNode::outputNodeConnections() const {
  return mOutputNodeConnections;
}

const std::vector<AbstractNodeConnection *>
AbstractNode::nodeConnections() const {
  std::vector<AbstractNodeConnection *> nodeConnections = mInputNodeConnections;
  nodeConnections.insert(nodeConnections.end(), mOutputNodeConnections.begin(),
                         mOutputNodeConnections.end());
  return nodeConnections;
}

} // namespace NodeNetwork
} // namespace Shared
