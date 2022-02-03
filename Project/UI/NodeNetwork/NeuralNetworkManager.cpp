#include "NeuralNetworkManager.h"
#include "NeuralNetwork.h"

// test
#include "UI/Application/CentralWidget.h"
#include "UI/Application/CentralWidgetView.h"
// test

namespace UI {
namespace NodeNetwork {

NeuralNetworkManager::NeuralNetworkManager(QObject *parent)
    : Shared::NodeNetwork::NodeNetworkManager(parent) {
  auto &communicator = Shared::Communicator::Communicator::instance();
  communicator.connect(
      this, {Shared::Communicator::EvNeuralNetCreateResponse::staticType(),
             Shared::Communicator::EvNeuralNetRunInfo::staticType()});
}

NeuralNetworkManager::~NeuralNetworkManager() {}

QUuid NeuralNetworkManager::createMeshNetwork(
    const std::vector<unsigned long> &layerSizes, const double learningRate,
    const std::optional<unsigned> seed) {

  NeuralNetwork *neuralNetwork = new NeuralNetwork(this);

  // View created without a parent.
  neuralNetwork->initView();

  const QUuid &networkId =
      Shared::NodeNetwork::NodeNetworkManager::buildMeshNetwork(neuralNetwork,
                                                                layerSizes);

  auto &communicator = Shared::Communicator::Communicator::instance();
  communicator.postEvent(new Shared::Communicator::EvNeuralNetCreate(
      layerSizes, learningRate, seed, networkId));

  return networkId;
}

void NeuralNetworkManager::runTest(const QUuid &networkId,
                                   const ulong learningIterations,
                                   const ulong testingIterations,
                                   const std::optional<ulong> dataSeed) {
  auto &communicator = Shared::Communicator::Communicator::instance();
  communicator.postEvent(new Shared::Communicator::EvNeuralNetRun(
      networkId, learningIterations, testingIterations, dataSeed));
}

void NeuralNetworkManager::customEvent(QEvent *event) {
  const auto type = event->type();

  if (type == Shared::Communicator::EvNeuralNetCreateResponse::staticType()) {
    auto *ev =
        static_cast<Shared::Communicator::EvNeuralNetCreateResponse *>(event);

    if (!ev->networkId.has_value()) {
      return;
    }

    // TODO: handle response

  } else if (type == Shared::Communicator::EvNeuralNetRunInfo::staticType()) {
    // populate the corresponding UI network with the values.
    auto *ev = static_cast<Shared::Communicator::EvNeuralNetRunInfo *>(event);

    auto &netId = ev->networkId;
    auto &network = this->network<NeuralNetwork>(netId);
    network.setData(ev->networkData);

    // test
    static_cast<UI::Application::CentralWidget *>(parent())
        ->view()
        ->scene()
        ->update();
    static_cast<UI::Application::CentralWidget *>(parent())->view()->repaint();
    qt_noop();
    // test
  }
}

} // namespace NodeNetwork
} // namespace UI
