#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/Neuron.h"
#include "NodeNetwork/NodeConnection.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : mScene(new QGraphicsScene(parent)), mView(new CentralWidgetView(mScene)) {

  // addNeuron();

  using Neuron = UI::NodeNetwork::Neuron;
  using NodeConnection = UI::NodeNetwork::NodeConnection;

  // TODO: fix parent relation here
  Neuron *node1 = new Neuron();
  Neuron *node2 = new Neuron();
  Neuron *node3 = new Neuron();
  Neuron *node4 = new Neuron();
  Neuron *centerNode = new Neuron();
  Neuron *node6 = new Neuron();
  Neuron *node7 = new Neuron();
  Neuron *node8 = new Neuron();
  Neuron *node9 = new Neuron();
  mScene->addItem(node1->view());
  mScene->addItem(node2->view());
  mScene->addItem(node3->view());
  mScene->addItem(node4->view());
  mScene->addItem(centerNode->view());
  mScene->addItem(node6->view());
  mScene->addItem(node7->view());
  mScene->addItem(node8->view());
  mScene->addItem(node9->view());

  node1->view()->setPos(-50, -50);
  node2->view()->setPos(0, -50);
  node3->view()->setPos(50, -50);
  node4->view()->setPos(-50, 0);
  centerNode->view()->setPos(0, 0);
  node6->view()->setPos(50, 0);
  node7->view()->setPos(-50, 50);
  node8->view()->setPos(0, 50);
  node9->view()->setPos(50, 50);

  // TODO: fix parent relation here
  NodeConnection *nodeConnection1 = new NodeConnection(node1, node2);
  NodeConnection *nodeConnection2 = new NodeConnection(node2, node3);
  NodeConnection *nodeConnection3 = new NodeConnection(node2, centerNode);
  NodeConnection *nodeConnection4 = new NodeConnection(node3, node6);
  NodeConnection *nodeConnection5 = new NodeConnection(node4, node1);
  NodeConnection *nodeConnection6 = new NodeConnection(node4, centerNode);
  NodeConnection *nodeConnection7 = new NodeConnection(centerNode, node6);
  NodeConnection *nodeConnection8 = new NodeConnection(centerNode, node8);
  NodeConnection *nodeConnection9 = new NodeConnection(node6, node9);
  NodeConnection *nodeConnection10 = new NodeConnection(node7, node4);
  NodeConnection *nodeConnection11 = new NodeConnection(node8, node7);
  NodeConnection *nodeConnection12 = new NodeConnection(node9, node8);

  mScene->addItem(nodeConnection1->view());
  mScene->addItem(nodeConnection2->view());
  mScene->addItem(nodeConnection3->view());
  mScene->addItem(nodeConnection4->view());
  mScene->addItem(nodeConnection5->view());
  mScene->addItem(nodeConnection6->view());
  mScene->addItem(nodeConnection7->view());
  mScene->addItem(nodeConnection8->view());
  mScene->addItem(nodeConnection9->view());
  mScene->addItem(nodeConnection10->view());
  mScene->addItem(nodeConnection11->view());
  mScene->addItem(nodeConnection12->view());
}

CentralWidgetView *CentralWidget::view() const { return mView; }

void CentralWidget::addNeuron() {
  using Neuron = UI::NodeNetwork::Neuron;
  auto *neuron = new Neuron();
  mScene->addItem(neuron->view());
}

} // namespace Application
} // namespace UI
