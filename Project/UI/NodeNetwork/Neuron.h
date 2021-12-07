#ifndef NeuronController_H
#define NeuronController_H

#include "UI/NodeNetwork/Node.h"

namespace UI {
namespace NodeNetwork {

class Neuron : public Node {
  Q_OBJECT

public:
  Neuron(QObject *parent = Q_NULLPTR);

  ~Neuron();

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuronController_H
