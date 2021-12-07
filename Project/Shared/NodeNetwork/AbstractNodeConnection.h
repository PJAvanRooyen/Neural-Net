#ifndef AbstractNodeConnection_H
#define AbstractNodeConnection_H

namespace Shared {
namespace NodeNetwork {

class AbstractNode;

class AbstractNodeConnection {
public:
  AbstractNodeConnection(AbstractNode *sourceNode, AbstractNode *destNode);

  ~AbstractNodeConnection();

  AbstractNode *sourceNode() const;
  AbstractNode *destinationNode() const;

private:
  AbstractNode *mSource, *mDestination;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeConnection_H
