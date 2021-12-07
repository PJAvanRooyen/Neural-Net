#include "Neuron.h"
#include "NeuronView.h"

namespace UI {
namespace NodeNetwork {

Neuron::Neuron(QObject *parent) : Node(parent) {}

Neuron::~Neuron(){};

QGraphicsItem *Neuron::createView(QGraphicsItem *parentView) {
  return new NeuronView(parentView);
}

} // namespace NodeNetwork
} // namespace UI