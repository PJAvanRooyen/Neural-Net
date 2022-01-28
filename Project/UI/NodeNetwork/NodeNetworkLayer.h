#ifndef NodeNetworkLayerController_H
#define NodeNetworkLayerController_H

#include "Shared/NodeNetwork/AbstractNodeNetworkLayer.h"
#include "UI/GraphicsItem/AbstractGraphicsItemController.h"
#include "UI/NodeNetwork/Node.h"

namespace UI {
namespace NodeNetwork {

class NodeNetworkLayer : public AbstractGraphicsItemController,
                         public Shared::NodeNetwork::AbstractNodeNetworkLayer {
public:
  NodeNetworkLayer(QObject *parent = Q_NULLPTR);

  virtual Shared::NodeNetwork::AbstractNode *addNode() override;

  template <class DerivedNodeNetworkLayerView, class DerivedNodeView>
  void addNode(Node *node) {
    AbstractNodeNetworkLayer::addNode(node);

    view<DerivedNodeNetworkLayerView>()->addNode(node->view<DerivedNodeView>());
  }

  template <class DerivedNodeNetworkLayerView, class DerivedNodeView>
  void addNodes(std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) {
    for (auto *node : nodes) {
      addNode<DerivedNodeNetworkLayerView, DerivedNodeView>(node);
    }
  }

protected:
  QGraphicsItem *createViewBase(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkLayerController_H
