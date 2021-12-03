#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/Node/Neuron.h"
#include "NodeNetwork/Node/NodeConnection.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : mScene(new QGraphicsScene(parent)), mView(new CentralWidgetView(mScene)) {

  // addNeuron();

  // TODO: fix parent relation here
  UI::Node::Neuron *node1 = new UI::Node::Neuron();
  UI::Node::Neuron *node2 = new UI::Node::Neuron();
  UI::Node::Neuron *node3 = new UI::Node::Neuron();
  UI::Node::Neuron *node4 = new UI::Node::Neuron();
  UI::Node::Neuron *centerNode = new UI::Node::Neuron();
  UI::Node::Neuron *node6 = new UI::Node::Neuron();
  UI::Node::Neuron *node7 = new UI::Node::Neuron();
  UI::Node::Neuron *node8 = new UI::Node::Neuron();
  UI::Node::Neuron *node9 = new UI::Node::Neuron();
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
  UI::Node::NodeConnection *nodeConnection1 =
      new UI::Node::NodeConnection(node1, node2);
  UI::Node::NodeConnection *nodeConnection2 =
      new UI::Node::NodeConnection(node2, node3);
  UI::Node::NodeConnection *nodeConnection3 =
      new UI::Node::NodeConnection(node2, centerNode);
  UI::Node::NodeConnection *nodeConnection4 =
      new UI::Node::NodeConnection(node3, node6);
  UI::Node::NodeConnection *nodeConnection5 =
      new UI::Node::NodeConnection(node4, node1);
  UI::Node::NodeConnection *nodeConnection6 =
      new UI::Node::NodeConnection(node4, centerNode);
  UI::Node::NodeConnection *nodeConnection7 =
      new UI::Node::NodeConnection(centerNode, node6);
  UI::Node::NodeConnection *nodeConnection8 =
      new UI::Node::NodeConnection(centerNode, node8);
  UI::Node::NodeConnection *nodeConnection9 =
      new UI::Node::NodeConnection(node6, node9);
  UI::Node::NodeConnection *nodeConnection10 =
      new UI::Node::NodeConnection(node7, node4);
  UI::Node::NodeConnection *nodeConnection11 =
      new UI::Node::NodeConnection(node8, node7);
  UI::Node::NodeConnection *nodeConnection12 =
      new UI::Node::NodeConnection(node9, node8);

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
  auto *neuron = new UI::Node::Neuron;
  mScene->addItem(neuron->view());
}

} // namespace Application
} // namespace UI
