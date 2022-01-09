#ifndef NeuronView_H
#define NeuronView_H

#include "UI/NodeNetwork/NodeView.h"

namespace UI {
namespace NodeNetwork {

class NeuronView : public NodeView {
public:
  NeuronView(QGraphicsItem *parent = Q_NULLPTR);
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuronView_H
