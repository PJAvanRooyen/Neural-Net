#ifndef NeuronController_H
#define NeuronController_H

#include "UI/NodeNetwork/Node.h"

namespace Shared {
namespace NodeNetwork {
template <typename DataType> class NeuronData;
}
} // namespace Shared

namespace UI {
namespace NodeNetwork {

class NeuronConnection;

class Neuron : public Node {
  Q_OBJECT

public:
  Neuron(QObject *parent = Q_NULLPTR);

  ~Neuron();

  void setData(const Shared::NodeNetwork::NeuronData<double> &neuronData);

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuronController_H
