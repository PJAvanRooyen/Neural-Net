#ifndef NodeNetworkLayerController_H
#define NodeNetworkLayerController_H

#include "Shared/NodeNetwork/AbstractNodeNetworkLayer.h"
#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

namespace UI {
namespace NodeNetwork {

class NodeNetworkLayer : public AbstractGraphicsItemController,
                         public Shared::NodeNetwork::AbstractNodeNetworkLayer {
public:
  NodeNetworkLayer(QObject *parent = Q_NULLPTR);

  void addNode(Shared::NodeNetwork::AbstractNode *node) override;

  void
  addNodes(std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) override;

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkLayerController_H
