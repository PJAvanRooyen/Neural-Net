#include "NeuralNetworkManager.h"
#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkFactory.h"
#include "Shared/Communicator/Communicator.h"

// test
#include "NeuralNetworkTester.h"
// test

namespace Core {
namespace NodeNetwork {

NeuralNetworkManager::NeuralNetworkManager(QObject *parent)
    : NodeNetworkManager(parent) {
  auto &communicator = Shared::Communicator::Communicator::instance();
  communicator.connect(this,
                       {Shared::Communicator::EvNeuralNetCreate::staticType(),
                        Shared::Communicator::EvNeuralNetRun::staticType()});
}

NeuralNetworkManager::~NeuralNetworkManager() {}

NeuralNetwork<double> *NeuralNetworkManager::createMeshNetwork(
    const std::vector<unsigned long> &layerSizes, const double learningRate,
    const std::optional<unsigned> seed, const QUuid &networkId) {

  auto *neuralNetwork = NeuralNetworkFactory::createMeshNetwork<double>(
      layerSizes, learningRate, seed);

  addNetwork(networkId, neuralNetwork);

  return neuralNetwork;
}

void NeuralNetworkManager::customEvent(QEvent *event) {
  const auto type = event->type();

  if (type == Shared::Communicator::EvNeuralNetCreate::staticType()) {
    auto *ev = static_cast<Shared::Communicator::EvNeuralNetCreate *>(event);

    auto *netualNet = createMeshNetwork(ev->layerSizes, ev->learningRate,
                                        ev->seed, ev->networkId);

    if (!netualNet) {
      return;
    }

    auto &communicator = Shared::Communicator::Communicator::instance();
    communicator.postEvent(
        new Shared::Communicator::EvNeuralNetCreateResponse(ev->networkId));

  } else if (type == Shared::Communicator::EvNeuralNetRun::staticType()) {
    auto *ev = static_cast<Shared::Communicator::EvNeuralNetRun *>(event);

    NeuralNetworkTester::irisTest(
        ev->dataSeed, ev->learningIterations, ev->testingIterations,
        ev->networkId, network<NeuralNetwork<double>>(ev->networkId), true);
  }
}

} // namespace NodeNetwork
} // namespace Core
