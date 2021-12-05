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

  void addInputNodeConnection(NodeConnection *nodeConnection);
  std::vector<NodeConnection *> inputNodeConnections() const;

  void addOutputNodeConnection(NodeConnection *nodeConnection);
  std::vector<NodeConnection *> outputNodeConnections() const;

  std::vector<NodeConnection *> nodeConnections() const;

protected:
  std::vector<NodeConnection *> mInputNodeConnections;
  std::vector<NodeConnection *> mOutputNodeConnections;
};

} // namespace NodeNetwork
} // namespace Core

#endif // Node_H
