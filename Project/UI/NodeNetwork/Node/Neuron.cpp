#include "Neuron.h"
#include "NeuronView.h"

namespace UI {
namespace Node {

Neuron::Neuron(QObject *parent) : Node(parent) {}

Neuron::~Neuron(){};

QGraphicsItem *Neuron::createView(QGraphicsItem *parentView) {
  return new NeuronView(parentView);
}

} // namespace Node
} // namespace UI
