#ifndef NodeController_H
#define NodeController_H

#include "Shared/NodeNetwork/AbstractNode.h"
#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

namespace UI {
namespace NodeNetwork {

class NodeConnection;

class Node : public AbstractGraphicsItemController,
             public Shared::NodeNetwork::AbstractNode {
  Q_OBJECT

public:
  Node(QObject *parent = Q_NULLPTR);

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;

  // AbstractNode interface
public:
  void addInputNodeConnection(
      Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) override;

  void addInputNodeConnections(
      std::vector<Shared::NodeNetwork::AbstractNodeConnection *>
          &nodeConnections) override;

  void addOutputNodeConnection(
      Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) override;

  void addOutputNodeConnections(
      std::vector<Shared::NodeNetwork::AbstractNodeConnection *>
          &nodeConnections) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NodeController_H
