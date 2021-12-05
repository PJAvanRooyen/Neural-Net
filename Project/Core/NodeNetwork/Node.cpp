#include "Node.h"

namespace Core {
namespace NodeNetwork {

Node::Node() {}

Node::~Node() {}

void Node::addInputNodeConnection(NodeConnection *nodeConnection) {
  mInputNodeConnections.push_back(nodeConnection);
}
std::vector<NodeConnection *> Node::inputNodeConnections() const {
  return mInputNodeConnections;
}

void Node::addOutputNodeConnection(NodeConnection *nodeConnection) {
  mOutputNodeConnections.push_back(nodeConnection);
}
std::vector<NodeConnection *> Node::outputNodeConnections() const {
  return mOutputNodeConnections;
}

std::vector<NodeConnection *> Node::nodeConnections() const {
  std::vector<NodeConnection *> nodeConnections = mInputNodeConnections;
  nodeConnections.insert(nodeConnections.end(), mOutputNodeConnections.begin(),
                         mOutputNodeConnections.end());
  return nodeConnections;
}

} // namespace NodeNetwork
} // namespace Core
