#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NodeNetwork/NeuralNetworkFactory.h"
#include "NodeNetwork/NodeNetwork.h"
#include "NodeNetwork/NodeNetworkView.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : mScene(new QGraphicsScene(parent)), mView(new CentralWidgetView(mScene)) {

  using NeuralNetworkFactory = UI::NodeNetwork::NeuralNetworkFactory;
  using NeuralNetwork = UI::NodeNetwork::NodeNetwork;

  NeuralNetworkFactory factory = NeuralNetworkFactory();
  Shared::NodeNetwork::AbstractNodeNetwork *abstractNet =
      factory.createMeshNetwork({5, 6, 7, 3});
  NeuralNetwork *neuralNet = static_cast<NeuralNetwork *>(abstractNet);

  mScene->addItem(neuralNet->view<UI::NodeNetwork::NodeNetworkView>());

  mScene->update();
}

CentralWidgetView *CentralWidget::view() const { return mView; }

} // namespace Application
} // namespace UI
