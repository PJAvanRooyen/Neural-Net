#include "Core/ModuleManager/ModuleManager.h"
#include "Core/NeuralNetwork/NeuralNetworkManager.h"
#include "UI/Application/Application.h"
#include "UI/Application/ApplicationView.h"

#include <QApplication>

int main(int argc, char *argv[]) {

  // CORE
  //=========================================================================
  auto nnm = Core::NodeNetwork::NeuralNetworkManager();

  // UI
  //=========================================================================
  QApplication a(argc, argv);
  UI::Application::Application application = UI::Application::Application();

  application.view()->show();

  return a.exec();
}
