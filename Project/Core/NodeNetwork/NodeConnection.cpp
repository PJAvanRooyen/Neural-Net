#include "NodeConnection.h"
#include "Node.h"

namespace Core {
namespace NodeNetwork {

NodeConnection::NodeConnection(Node *sourceNode, Node *destNode)
    : mSource(sourceNode), mDestination(destNode) {

  // note: connections are only done in a forward direction.
  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
}

NodeConnection::~NodeConnection() {}

Node *NodeConnection::sourceNode() const { return mSource; }

Node *NodeConnection::destNode() const { return mDestination; }

} // namespace NodeNetwork
} // namespace Core
