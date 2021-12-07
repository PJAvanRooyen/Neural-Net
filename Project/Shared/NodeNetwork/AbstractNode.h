#ifndef AbstractNode_H
#define AbstractNode_H

#include <vector>

namespace Shared {
namespace NodeNetwork {

class AbstractNodeConnection;

class AbstractNode {
public:
  AbstractNode();

  ~AbstractNode();

  virtual void addInputNodeConnection(AbstractNodeConnection *nodeConnection);

  virtual void addInputNodeConnections(
      std::vector<AbstractNodeConnection *> &nodeConnections);

  const std::vector<AbstractNodeConnection *> &inputNodeConnections() const;

  virtual void addOutputNodeConnection(AbstractNodeConnection *nodeConnection);

  virtual void addOutputNodeConnections(
      std::vector<AbstractNodeConnection *> &nodeConnections);

  const std::vector<AbstractNodeConnection *> &outputNodeConnections() const;

  const std::vector<AbstractNodeConnection *> nodeConnections() const;

protected:
  std::vector<AbstractNodeConnection *> mInputNodeConnections;
  std::vector<AbstractNodeConnection *> mOutputNodeConnections;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNode_H
