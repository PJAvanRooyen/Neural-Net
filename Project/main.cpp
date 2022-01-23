#include "Core/ModuleManager/ModuleManager.h"
#include "Core/NeuralNetwork/NeuralNetworkManager.h"
#include "UI/Application/Application.h"

// test
// #include "../Tests/Core/NeuralNet/NeuralNetTest.h"
// test

#include <QApplication>

int main(int argc, char *argv[]) {

  // Tests::NeuralNetTest::irisTest();

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
