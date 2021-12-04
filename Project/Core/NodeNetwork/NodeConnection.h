#ifndef NodeConnection_H
#define NodeConnection_H

namespace Core {
namespace NodeNetwork {

class Node;

class NodeConnection {
public:
  NodeConnection(Node *sourceNode, Node *destNode);

  ~NodeConnection();

  Node *sourceNode() const;
  Node *destNode() const;

private:
  Node *mSource, *mDestination;
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeConnection_H
