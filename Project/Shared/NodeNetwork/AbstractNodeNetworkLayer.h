#ifndef AbstractNodeNetworkLayer_H
#define AbstractNodeNetworkLayer_H

#include "AbstractNode.h"

#include <vector>

namespace Shared {
namespace NodeNetwork {

class AbstractNodeNetworkLayer : public AbstractNode {
public:
  AbstractNodeNetworkLayer();

  ~AbstractNodeNetworkLayer();

  const std::vector<AbstractNode *> &nodes() const;

  virtual void addNode(AbstractNode *node);

  virtual void addNodes(std::vector<AbstractNode *> &nodes);

private:
  std::vector<AbstractNode *> mNodes;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeNetworkLayer_H
