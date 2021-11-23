#ifndef Neuron_H
#define Neuron_H

#include "UI/GraphicsItem/AbstractGraphicsItemController.h"

#include <QGraphicsItem>

namespace UI {

namespace Neuron {

class Neuron : public AbstractGraphicsItemController {
  Q_OBJECT

public:
  Neuron(QObject *parent = Q_NULLPTR);

  ~Neuron();

protected:
  QGraphicsItem *createView(QGraphicsItem *parentView) override;
};

} // namespace Neuron
} // namespace UI
#endif // NeuronView_H
