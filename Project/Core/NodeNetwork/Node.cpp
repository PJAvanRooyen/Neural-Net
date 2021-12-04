#include "Node.h"

namespace Core {
namespace NodeNetwork {

Node::Node() {}

Node::~Node() {}

void Node::addNodeConnection(NodeConnection *nodeConnection) {
  mNodeConnections.push_back(nodeConnection);
}

std::vector<NodeConnection *> Node::nodeConnections() const {
  return mNodeConnections;
}

} // namespace NodeNetwork
} // namespace Core
