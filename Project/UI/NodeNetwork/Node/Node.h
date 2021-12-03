#ifndef NodeUI_H
#define NodeUI_H

#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

#include <QGraphicsItem>

namespace UI {

namespace Node {

class Node : public AbstractGraphicsItemController {
  Q_OBJECT

public:
  Node(QObject *parent = Q_NULLPTR);

  ~Node();

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace Node
} // namespace UI
#endif // NodeUI_H
