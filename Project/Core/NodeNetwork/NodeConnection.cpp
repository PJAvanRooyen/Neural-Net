#include "NodeConnection.h"
#include "Node.h"

namespace Core {
namespace NodeNetwork {

NodeConnection::NodeConnection(Node *sourceNode, Node *destNode)
    : mSource(sourceNode), mDestination(destNode) {
  mSource->addNodeConnection(this);
  mDestination->addNodeConnection(this);
}

NodeConnection::~NodeConnection() {}

Node *NodeConnection::sourceNode() const { return mSource; }

Node *NodeConnection::destNode() const { return mDestination; }

} // namespace NodeNetwork
} // namespace Core
