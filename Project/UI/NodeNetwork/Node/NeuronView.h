#ifndef NeuronView_H
#define NeuronView_H

#include "UI/NodeNetwork/Node/NodeView.h"

namespace UI {
namespace Node {

class NeuronView : public NodeView {
public:
  NeuronView(QGraphicsItem *parent = Q_NULLPTR);
};

} // namespace Node
} // namespace UI
#endif // NeuronView_H
