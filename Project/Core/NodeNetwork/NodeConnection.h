#ifndef NodeConnection_H
#define NodeConnection_H

#include "Shared/NodeNetwork/AbstractNodeConnection.h"

namespace Core {
namespace NodeNetwork {

class Node;

class NodeConnection : public Shared::NodeNetwork::AbstractNodeConnection {
public:
  NodeConnection(Node *sourceNode, Node *destNode);
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeConnection_H
