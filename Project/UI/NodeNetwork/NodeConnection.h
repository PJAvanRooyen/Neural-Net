#ifndef NodeConnectionController_H
#define NodeConnectionController_H

#include "Shared/NodeNetwork/AbstractNodeConnection.h"
#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

namespace UI {
namespace NodeNetwork {

class Node;

class NodeConnection : public AbstractGraphicsItemController,
                       public Shared::NodeNetwork::AbstractNodeConnection {
  Q_OBJECT

public:
  NodeConnection(Node *sourceNode, Node *destNode, QObject *parent = Q_NULLPTR);

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NodeConnectionController_H
