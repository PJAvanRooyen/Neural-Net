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

QList<QUuid> CentralWidget::availableNetworks() const {
  return mNetworkManager.availableNetworks();
}

QUuid CentralWidget::createTestNetwork(
    const std::vector<unsigned long> &layerSizes,
    const std::optional<unsigned> seed, const double learningRate) {
  using NeuralNetwork = UI::NodeNetwork::NeuralNetwork;

  const QUuid &networkId =
      mNetworkManager.createMeshNetwork(layerSizes, learningRate, seed);
  NeuralNetwork &neuralNet = mNetworkManager.network<NeuralNetwork>(networkId);

  auto *neuralNetView = neuralNet.view<UI::NodeNetwork::NodeNetworkView>();
  mScene->addItem(neuralNetView);
  neuralNetView->show();

  return networkId;
}

void CentralWidget::runTest(const QUuid &networkId,
                            const ulong learningIterations,
                            const ulong testingIterations,
                            const std::optional<ulong> dataSeed) {
  mNetworkManager.runTest(networkId, learningIterations, testingIterations,
                          dataSeed);
}

CentralWidgetView *CentralWidget::view() const { return mView; }

} // namespace Application
} // namespace UI
