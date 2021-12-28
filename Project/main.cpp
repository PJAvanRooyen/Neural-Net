#include "Core/ModuleManager/ModuleManager.h"
#include "UI/Application/Application.h"

// test
#include "Core/NeuralNetwork/Neuron.h"
// test

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // test
  Core::NodeNetwork::Neuron<double> *l1n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l1n2 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l2n1 =
      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::NeuronConnection c_l1n1_l2n1 =
      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n1);
  c_l1n1_l2n1.setInputValue(l1n1->bias());

  Core::NodeNetwork::NeuronConnection c_l1n2_l2n1 =
      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n1);
  c_l1n2_l2n1.setInputValue(l1n2->bias());

  l2n1->activate();

  // test

  UI::Application::Application application = UI::Application::Application();

  application.view()->show();

  return a.exec();
}
