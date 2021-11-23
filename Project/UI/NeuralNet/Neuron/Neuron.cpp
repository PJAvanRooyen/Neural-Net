#include "Neuron.h"
#include "NeuronView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace Neuron {

Neuron::Neuron(QObject *parent) : AbstractGraphicsItemController(parent) {}

Neuron::~Neuron(){};

QGraphicsItem *Neuron::createView(QGraphicsItem *parentView) {
  return new NeuronView(parentView);
}

} // namespace Neuron
} // namespace UI
