#include "Core/ModuleManager/ModuleManager.h"
#include "Core/NeuralNetwork/NeuralNetworkManager.h"
#include "Shared/Communicator/Communicator.h"
#include "UI/Application/Application.h"
#include "UI/Application/ApplicationView.h"

#include <QApplication>
#include <QThread>

// #define RUN_UNIT_TESTS

#ifdef RUN_UNIT_TESTS
#include "../Tests/Core/NeuralNetwork/NeuralNetworkTest.h"
#endif

int main(int argc, char *argv[]) {

#ifdef RUN_UNIT_TESTS
  Q_UNUSED(argc)
  Q_UNUSED(argv)
  Tests::NeuralNetTest::singleIterationTest();
#else

  QThread coreThread = QThread();
  // COMMUNICATOR
  //=========================================================================
  auto &comm = Shared::Communicator::Communicator::instance();
  comm.moveToThread(&coreThread);

  // CORE
  //=========================================================================
  auto nnm = Core::NodeNetwork::NeuralNetworkManager();
  nnm.moveToThread(&coreThread);

  // UI
  //=========================================================================
  QApplication a(argc, argv);
  UI::Application::Application application = UI::Application::Application();
  coreThread.start();

  return a.exec();
#endif
}
