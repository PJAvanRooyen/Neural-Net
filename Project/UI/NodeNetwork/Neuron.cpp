#include "Neuron.h"
#include "NeuronView.h"

namespace UI {
namespace NodeNetwork {

Neuron::Neuron(QObject *parent) : Node(parent) {}

Neuron::~Neuron() {}

void Neuron::setData(
    const Shared::NodeNetwork::NeuronData<double> &neuronData) {
  auto *view = this->view<NeuronView>();
  view->setData(neuronData);
};

QGraphicsItem *Neuron::createView(QGraphicsItem *parentView) {
  return new NeuronView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
