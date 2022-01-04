#ifndef NodeNetworkFactoryUI_H
#define NodeNetworkFactoryUI_H

#include "UI/NodeNetwork/Node.h"

namespace UI {
namespace NodeNetworkFactory {

class Neuron : public Node {
  Q_OBJECT

public:
  Neuron(QObject *parent = Q_NULLPTR);

  ~Neuron();

protected:
  QGraphicsItem *createViewBase(QGraphicsItem *parentView) override;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NodeNetworkFactoryUI_H
