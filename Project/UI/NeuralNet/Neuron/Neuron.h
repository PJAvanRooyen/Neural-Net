#ifndef Neuron_H
#define Neuron_H

#include "UI/Widget/AbstractWidget.h"

namespace UI {
namespace Neuron {

class Neuron : public AbstractWidget {
  Q_OBJECT

public:
  Neuron(QObject *parent);

  ~Neuron();

protected:
  QWidget *createView(QWidget *parentView) override;
};

} // namespace Neuron
} // namespace UI
#endif // NeuronView_H
