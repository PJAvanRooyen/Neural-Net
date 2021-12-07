#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/Neuron.h"
#include "NodeNetwork/NodeConnection.h"

#include "NodeNetwork/NodeNetwork.h"
#include "NodeNetwork/NodeNetworkLayer.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : mScene(new QGraphicsScene(parent)), mView(new CentralWidgetView(mScene)) {

  // addNeuron();
  using AbstractNode = Shared::NodeNetwork::AbstractNode;
  using Neuron = UI::NodeNetwork::Neuron;
  using NodeConnection = UI::NodeNetwork::NodeConnection;

  // TODO: fix parent relation here
  using NodeNetwork = UI::NodeNetwork::NodeNetwork;
  using AbstractNodeNetworkLayer =
      Shared::NodeNetwork::AbstractNodeNetworkLayer;
  using NodeNetworkLayer = UI::NodeNetwork::NodeNetworkLayer;

  NodeNetwork *nodeNetwork = new NodeNetwork();

  NodeNetworkLayer *layerA = new NodeNetworkLayer(nodeNetwork);
  NodeNetworkLayer *layerB = new NodeNetworkLayer(nodeNetwork);
  NodeNetworkLayer *layerC = new NodeNetworkLayer(nodeNetwork);

  Neuron *nodeA1 = new Neuron(layerA);
  Neuron *nodeA2 = new Neuron(layerA);
  Neuron *nodeA3 = new Neuron(layerA);
  Neuron *nodeB1 = new Neuron(layerB);
  Neuron *nodeB2 = new Neuron(layerB);
  Neuron *nodeB3 = new Neuron(layerB);
  Neuron *nodeC1 = new Neuron(layerC);
  Neuron *nodeC2 = new Neuron(layerC);
  Neuron *nodeC3 = new Neuron(layerC);

  NodeConnection *nodeConnectionA1B1 =
      new NodeConnection(nodeA1, nodeB1, nodeNetwork);
  NodeConnection *nodeConnectionA1B2 =
      new NodeConnection(nodeA1, nodeB2, nodeNetwork);
  NodeConnection *nodeConnectionA1B3 =
      new NodeConnection(nodeA1, nodeB3, nodeNetwork);
  NodeConnection *nodeConnectionA2B1 =
      new NodeConnection(nodeA2, nodeB1, nodeNetwork);
  NodeConnection *nodeConnectionA2B2 =
      new NodeConnection(nodeA2, nodeB2, nodeNetwork);
  NodeConnection *nodeConnectionA2B3 =
      new NodeConnection(nodeA2, nodeB3, nodeNetwork);
  NodeConnection *nodeConnectionA3B1 =
      new NodeConnection(nodeA3, nodeB1, nodeNetwork);
  NodeConnection *nodeConnectionA3B2 =
      new NodeConnection(nodeA3, nodeB2, nodeNetwork);
  NodeConnection *nodeConnectionA3B3 =
      new NodeConnection(nodeA3, nodeB3, nodeNetwork);

  NodeConnection *nodeConnectionB1C1 =
      new NodeConnection(nodeB1, nodeC1, nodeNetwork);
  NodeConnection *nodeConnectionB1C2 =
      new NodeConnection(nodeB1, nodeC2, nodeNetwork);
  NodeConnection *nodeConnectionB1C3 =
      new NodeConnection(nodeB1, nodeC3, nodeNetwork);
  NodeConnection *nodeConnectionB2C1 =
      new NodeConnection(nodeB2, nodeC1, nodeNetwork);
  NodeConnection *nodeConnectionB2C2 =
      new NodeConnection(nodeB2, nodeC2, nodeNetwork);
  NodeConnection *nodeConnectionB2C3 =
      new NodeConnection(nodeB2, nodeC3, nodeNetwork);
  NodeConnection *nodeConnectionB3C1 =
      new NodeConnection(nodeB3, nodeC1, nodeNetwork);
  NodeConnection *nodeConnectionB3C2 =
      new NodeConnection(nodeB3, nodeC2, nodeNetwork);
  NodeConnection *nodeConnectionB3C3 =
      new NodeConnection(nodeB3, nodeC3, nodeNetwork);

  std::vector<AbstractNode *> nodesA = {nodeA1, nodeA2, nodeA3};
  layerA->addNodes(nodesA);

  std::vector<AbstractNode *> nodesB = {nodeB1, nodeB2, nodeB3};
  layerB->addNodes(nodesB);

  std::vector<AbstractNode *> nodesC = {nodeC1, nodeC2, nodeC3};
  layerC->addNodes(nodesC);

  std::vector<AbstractNodeNetworkLayer *> layers = {layerA, layerB, layerC};
  nodeNetwork->addLayers(layers);
  mScene->addItem(nodeNetwork->view());
}

CentralWidgetView *CentralWidget::view() const { return mView; }

void CentralWidget::addNeuron() {
  using Neuron = UI::NodeNetwork::Neuron;
  auto *neuron = new Neuron();
  mScene->addItem(neuron->view());
}

} // namespace Application
} // namespace UI
