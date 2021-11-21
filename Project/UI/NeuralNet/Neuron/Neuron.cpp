#include "Neuron.h"
#include "NeuronView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace Neuron {

Neuron::Neuron(QObject *parent) : AbstractWidget(parent) {}

Neuron::~Neuron(){};

QWidget *Neuron::createView(QWidget *parentView) {
  return new NeuronView(parentView);
}

} // namespace Neuron
} // namespace UI
