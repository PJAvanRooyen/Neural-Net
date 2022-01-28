#ifndef NeuronConnectionController_H
#define NeuronConnectionController_H

#include "UI/NodeNetwork/NodeConnection.h"

namespace Shared {
namespace NodeNetwork {
template <typename DataType> class NeuronConnectionData;
}
} // namespace Shared

namespace UI {
namespace NodeNetwork {

class Neuron;

class NeuronConnection : public UI::NodeNetwork::NodeConnection {
  Q_OBJECT

public:
  NeuronConnection(Neuron *sourceNode, Neuron *destNode,
                   AbstractGraphicsItemController *parent = Q_NULLPTR);

  ~NeuronConnection();

  void setData(
      const Shared::NodeNetwork::NeuronConnectionData<double> &connectionData);

protected:
  QGraphicsItem *createViewBase(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuronConnectionController_H
