#ifndef Neuron_H
#define Neuron_H

#include "UI/NodeNetwork/Node/Node.h"

namespace UI {
namespace Node {

class Neuron : public Node {
  Q_OBJECT

public:
  Neuron(QObject *parent = Q_NULLPTR);

  ~Neuron();

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace Node
} // namespace UI
#endif // NeuronView_H
