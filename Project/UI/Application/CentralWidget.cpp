#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/NodeNetworkView.h"
#include "UI/NodeNetwork/NeuralNetwork.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : QObject(parent), mScene(new QGraphicsScene(parent)),
      mView(new CentralWidgetView(mScene)),
      mNetworkManager(UI::NodeNetwork::NeuralNetworkManager(this)) {

  using NeuralNetwork = UI::NodeNetwork::NeuralNetwork;

  const std::vector<unsigned long> layerSizes = {5, 5, 3, 3};

  const QUuid &networkId =
      mNetworkManager.createMeshNetwork<NeuralNetwork>(layerSizes);
  NeuralNetwork &neuralNet = mNetworkManager.network<NeuralNetwork>(networkId);

  neuralNet.setParent(this);
  auto *neuralNetView = neuralNet.view<UI::NodeNetwork::NodeNetworkView>();
  mScene->addItem(neuralNetView);
}

CentralWidgetView *CentralWidget::view() const { return mView; }

} // namespace Application
} // namespace UI
