#ifndef NodeConnectionUI_H
#define NodeConnectionUI_H

#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

#include <QGraphicsItem>

namespace UI {
namespace Node {

class Node;

class NodeConnection : public AbstractGraphicsItemController {
  Q_OBJECT

public:
  NodeConnection(Node *sourceNode, Node *destNode, QObject *parent = Q_NULLPTR);

  ~NodeConnection();

  Node *sourceNode() const;
  Node *destNode() const;

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;

private:
  Node *mSource, *mDestination;
};

} // namespace Node
} // namespace UI
#endif // NodeConnectionUI_H
