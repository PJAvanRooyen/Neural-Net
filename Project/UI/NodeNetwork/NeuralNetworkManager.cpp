#include "NeuralNetworkManager.h"

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

void NeuralNetworkManager::customEvent(QEvent *event) {
  const auto type = event->type();

  if (type == Shared::Communicator::EvNeuralNetCreateResponse::staticType()) {
    auto *ev =
        static_cast<Shared::Communicator::EvNeuralNetCreateResponse *>(event);

    if (!ev->mNetId.has_value()) {
      return;
    }

    auto &communicator = Shared::Communicator::Communicator::instance();
    communicator.postEvent(
        new Shared::Communicator::EvNeuralNetRun(ev->mNetId.value()));

  } else if (type == Shared::Communicator::EvNeuralNetRunInfo::staticType()) {
    // populate the corresponding UI network with the values.
    qt_noop();
  }
}

} // namespace NodeNetwork
} // namespace UI
