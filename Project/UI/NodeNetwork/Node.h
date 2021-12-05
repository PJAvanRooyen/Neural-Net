#ifndef NodeUI_H
#define NodeUI_H

#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

#include <QGraphicsItem>

namespace UI {
namespace NodeNetwork {

class NodeConnection;

class Node : public AbstractGraphicsItemController {
  Q_OBJECT

public:
  Node(QObject *parent = Q_NULLPTR);

  ~Node();

  void addInputNodeConnection(NodeConnection *nodeConnection);
  QVector<NodeConnection *> inputNodeConnections() const;

  void addOutputNodeConnection(NodeConnection *nodeConnection);
  QVector<NodeConnection *> outputNodeConnections() const;

  QVector<NodeConnection *> nodeConnections() const;

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;

  QVector<NodeConnection *> mInputNodeConnections;
  QVector<NodeConnection *> mOutputNodeConnections;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NodeUI_H
