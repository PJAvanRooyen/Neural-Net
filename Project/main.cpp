#include "Core/ModuleManager/ModuleManager.h"
#include "Core/NeuralNetwork/NeuralNetworkManager.h"
#include "Shared/Communicator/Communicator.h"
#include "UI/Application/Application.h"
#include "UI/Application/ApplicationView.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]) {
  QThread coreThread = QThread();

  // COMMUNICATOR
  //=========================================================================
  auto &comm = Shared::Communicator::Communicator::instance();
  comm.moveToThread(&coreThread);

  // CORE
  //=========================================================================
  auto nnm = Core::NodeNetwork::NeuralNetworkManager();
  nnm.moveToThread(&coreThread);

  coreThread.start();

  // UI
  //=========================================================================
  QApplication a(argc, argv);
  UI::Application::Application application = UI::Application::Application();

  return a.exec();
}
