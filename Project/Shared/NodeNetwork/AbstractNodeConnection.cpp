#include "AbstractNodeConnection.h"
#include "AbstractNode.h"

namespace Shared {
namespace NodeNetwork {

AbstractNodeConnection::AbstractNodeConnection(AbstractNode *sourceNode,
                                               AbstractNode *destNode)
    : mSource(sourceNode), mDestination(destNode) {

  // note: connections are only done in a forward direction.
  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
}

AbstractNodeConnection::AbstractNodeConnection()
    : mSource(nullptr), mDestination(nullptr) {}

AbstractNodeConnection::~AbstractNodeConnection() {}

AbstractNode *AbstractNodeConnection::sourceNode() const { return mSource; }

AbstractNode *AbstractNodeConnection::destinationNode() const {
  return mDestination;
}

} // namespace NodeNetwork
} // namespace Shared
