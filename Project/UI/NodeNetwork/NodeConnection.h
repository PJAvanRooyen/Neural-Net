#ifndef NodeConnectionUI_H
#define NodeConnectionUI_H

#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

class Node;

class NodeConnection : public AbstractGraphicsItemController {
  Q_OBJECT

public:
  NodeConnection(Node *sourceNode, Node *destNode, QObject *parent = Q_NULLPTR);

  ~NodeConnection();

  Node *sourceNode() const;
  Node *destinationNode() const;

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;

private:
  Node *mSource, *mDestination;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NodeConnectionUI_H
