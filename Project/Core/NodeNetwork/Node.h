#ifndef Node_H
#define Node_H

#include <vector>

namespace Core {
namespace NodeNetwork {

class NodeConnection;

class Node {
public:
  Node();

  ~Node();

  void addNodeConnection(NodeConnection *nodeConnection);
  std::vector<NodeConnection *> nodeConnections() const;

protected:
  std::vector<NodeConnection *> mNodeConnections;
};

} // namespace NodeNetwork
} // namespace Core

#endif // Node_H
