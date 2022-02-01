#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/NodeNetworkView.h"
#include "UI/NodeNetwork/NeuralNetwork.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : QObject(parent), mScene(new QGraphicsScene(parent)),
      mView(new CentralWidgetView(mScene)),
      mNetworkManager(UI::NodeNetwork::NeuralNetworkManager(this)) {}

QUuid CentralWidget::createTestNetwork() {
  using NeuralNetwork = UI::NodeNetwork::NeuralNetwork;

  const std::vector<unsigned long> layerSizes = {5, 30, 30, 30, 30, 3};
  const double learningRate = 0.01;
  // nullopt means the seed is randomized
  const std::optional<unsigned> seed = std::nullopt;

  const QUuid &networkId =
      mNetworkManager.createMeshNetwork(layerSizes, learningRate, seed);
  NeuralNetwork &neuralNet = mNetworkManager.network<NeuralNetwork>(networkId);

  auto *neuralNetView = neuralNet.view<UI::NodeNetwork::NodeNetworkView>();
  mScene->addItem(neuralNetView);
  neuralNetView->show();
  mScene->update();
  view()->repaint();
  view()->show();

  return networkId;
}

void CentralWidget::runTest(const QUuid &networkId) {
  mNetworkManager.runTest(networkId);
}

CentralWidgetView *CentralWidget::view() const { return mView; }

} // namespace Application
} // namespace UI
