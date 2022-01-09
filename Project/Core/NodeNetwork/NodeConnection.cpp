#include "NodeConnection.h"
#include "Node.h"

namespace Core {
namespace NodeNetwork {

NodeConnection::NodeConnection(Node *sourceNode, Node *destNode)
    : Shared::NodeNetwork::AbstractNodeConnection(sourceNode, destNode) {}

} // namespace NodeNetwork
} // namespace Core
