#ifndef NodeNetworkLayer_H
#define NodeNetworkLayer_H

#include <vector>

namespace Core {
namespace NodeNetwork {

class Node;

class NodeNetworkLayer {
public:
  NodeNetworkLayer();

  ~NodeNetworkLayer();

  std::vector<Node *> nodes() const;

private:
  std::vector<Node *> mNodes;
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkLayer_H
