#ifndef AbstractNodeConnection_H
#define AbstractNodeConnection_H

namespace Shared {
namespace NodeNetwork {

class AbstractNode;

class AbstractNodeConnection {
public:
  AbstractNodeConnection(AbstractNode *sourceNode, AbstractNode *destNode);

  virtual ~AbstractNodeConnection();

  AbstractNode *sourceNode() const;
  AbstractNode *destinationNode() const;

protected:
  // used to pre-initialize derived class. derived class must handle setting the
  // members.
  AbstractNodeConnection();

  AbstractNode *mSource, *mDestination;
};

} // namespace NodeNetwork
} // namespace Shared

#endif // AbstractNodeConnection_H
