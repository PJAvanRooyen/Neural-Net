#ifndef AbstractNodeNetworkLayer_H
#define AbstractNodeNetworkLayer_H

#include "AbstractNode.h"

#include <vector>

namespace Shared {
namespace NodeNetwork {

class AbstractNodeNetworkLayer : public AbstractNode {
public:
  ~AbstractNodeNetworkLayer();

  const std::vector<AbstractNode *> &nodes() const;

  virtual Shared::NodeNetwork::AbstractNode *addNode() = 0;

  virtual void addNode(AbstractNode *node);

  virtual void addNodes(std::vector<AbstractNode *> &nodes);

protected:
  AbstractNodeNetworkLayer();

  std::vector<AbstractNode *> mNodes;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeNetworkLayer_H
