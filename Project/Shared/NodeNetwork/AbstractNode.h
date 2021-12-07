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

  void addInputNodeConnection(AbstractNodeConnection *nodeConnection);

  void addInputNodeConnections(
      std::vector<AbstractNodeConnection *> &nodeConnections);

  const std::vector<AbstractNodeConnection *> &inputNodeConnections() const;

  void addOutputNodeConnection(AbstractNodeConnection *nodeConnection);

  void addOutputNodeConnections(
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
