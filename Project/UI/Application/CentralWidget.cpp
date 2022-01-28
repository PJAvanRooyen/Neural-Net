#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/NodeNetworkView.h"
#include "UI/NodeNetwork/NeuralNetwork.h"
#include "UI/NodeNetwork/NeuralNetworkLayer.h"
#include "UI/NodeNetwork/Neuron.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : QObject(parent), mScene(new QGraphicsScene(parent)),
      mView(new CentralWidgetView(mScene)),
      mNetworkManager(UI::NodeNetwork::NeuralNetworkManager(this)) {}

bool CentralWidget::createMeshNetwork(
    const std::vector<unsigned long> &layerSizes) {
  using NeuralNetwork = UI::NodeNetwork::NeuralNetwork;

  auto *neuralNet =
      mNetworkManager.createMeshNetwork<NeuralNetwork>(layerSizes);

  neuralNet->setParent(this);
  mScene->addItem(neuralNet->view<UI::NodeNetwork::NodeNetworkView>());

  mScene->update();
  return true;
}

CentralWidgetView *CentralWidget::view() const { return mView; }

} // namespace Application
} // namespace UI
