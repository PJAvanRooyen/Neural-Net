#include "NeuronConnection.h"
#include "Neuron.h"
#include "NeuronConnectionView.h"
#include "NeuronView.h"

namespace UI {
namespace NodeNetwork {

NeuronConnection::NeuronConnection(Neuron *sourceNode, Neuron *destNode,
                                   AbstractGraphicsItemController *parent)
    : UI::NodeNetwork::NodeConnection() {
  setParent(parent);
  mSource = sourceNode;
  mDestination = destNode;

  // WARNING!
  // For all derived node connection types, it must first initialize
  // its base as empty, then create its own view.
  // This is necessary so that the correct derived view is created instead of
  // the base view.
  auto *nodeConnectionView = view<NeuronConnectionView>();
  sourceNode->view<NeuronView>()->addOutputNodeConnection(nodeConnectionView);
  destNode->view<NeuronView>()->addInputNodeConnection(nodeConnectionView);

  mSource->addOutputNodeConnection(this);
  mDestination->addInputNodeConnection(this);
}

NeuronConnection::~NeuronConnection(){};

void NeuronConnection::setData(
    const Shared::NodeNetwork::NeuronConnectionData<double> &connectionData) {
  auto *view = this->view<NeuronConnectionView>();
  view->setData(connectionData);
};

QGraphicsItem *NeuronConnection::createViewBase(QGraphicsItem *parentView) {
  return new NeuronConnectionView(
      static_cast<Neuron *>(sourceNode())->view<NeuronView>(),
      static_cast<Neuron *>(destinationNode())->view<NeuronView>(), parentView);
}

} // namespace NodeNetwork
} // namespace UI
