#include "Core/ModuleManager/ModuleManager.h"
#include "UI/Application/Application.h"

// test
#include "Core/NeuralNetwork/Neuron.h"
// test

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // start test
  Core::NodeNetwork::Neuron<double> *l1n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l1n2 =
      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::Neuron<double> *l2n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l2n2 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l2n3 =
      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::Neuron<double> *l3n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l3n2 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l3n3 =
      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::Neuron<double> *l4n1 =
      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::NeuronConnection c_l1n1_l2n1 =
      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n1);
  Core::NodeNetwork::NeuronConnection c_l1n2_l2n1 =
      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n1);

  Core::NodeNetwork::NeuronConnection c_l1n1_l2n2 =
      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n2);
  Core::NodeNetwork::NeuronConnection c_l1n2_l2n2 =
      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n2);

  Core::NodeNetwork::NeuronConnection c_l1n1_l2n3 =
      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n3);
  Core::NodeNetwork::NeuronConnection c_l1n2_l2n3 =
      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n3);

  Core::NodeNetwork::NeuronConnection c_l2n1_l3n1 =
      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n1);
  Core::NodeNetwork::NeuronConnection c_l2n2_l3n1 =
      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n1);
  Core::NodeNetwork::NeuronConnection c_l2n3_l3n1 =
      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n1);
  Core::NodeNetwork::NeuronConnection c_l2n1_l3n2 =
      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n2);
  Core::NodeNetwork::NeuronConnection c_l2n2_l3n2 =
      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n2);
  Core::NodeNetwork::NeuronConnection c_l2n3_l3n2 =
      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n2);
  Core::NodeNetwork::NeuronConnection c_l2n1_l3n3 =
      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n3);
  Core::NodeNetwork::NeuronConnection c_l2n2_l3n3 =
      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n3);
  Core::NodeNetwork::NeuronConnection c_l2n3_l3n3 =
      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n3);

  Core::NodeNetwork::NeuronConnection c_l3n1_l4n1 =
      Core::NodeNetwork::NeuronConnection<double>(l3n1, l4n1);
  Core::NodeNetwork::NeuronConnection c_l3n2_l4n1 =
      Core::NodeNetwork::NeuronConnection<double>(l3n2, l4n1);
  Core::NodeNetwork::NeuronConnection c_l3n3_l4n1 =
      Core::NodeNetwork::NeuronConnection<double>(l3n3, l4n1);

  std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  std::mt19937 engine; // Mersenne twister MT19937

  unsigned long long kLearningIterations = 1000000;
  unsigned long long kTestingIterations = 1000000;

  // learn
  srand(2);
  for (unsigned long long i = 0; i < kLearningIterations; ++i) {
    // set test value
    l1n1->setValue(rand() % 2);
    l1n2->setValue(rand() % 2);

    // activate
    l4n1->activate();

    // back propagate
    bool desiredValue =
        static_cast<bool>(l1n1->value()) && !static_cast<bool>(l1n2->value());
    l4n1->backPropagate(desiredValue);

    qt_noop();
  }

  // test result
  double correct = 0.0;
  for (unsigned long long i = 0; i < kTestingIterations; ++i) {
    // set test value
    l1n1->setValue(rand() % 2);
    l1n2->setValue(rand() % 2);

    // activate
    const double activation = l4n1->activate();

    bool obtainedValue = std::round(activation);
    bool desiredValue =
        static_cast<bool>(l1n1->value()) && !static_cast<bool>(l1n2->value());
    if (obtainedValue == desiredValue) {
      ++correct;
    } else {
      qt_noop();
    }
  }

  double accuracy = 100 * correct / kTestingIterations;
  Q_UNUSED(accuracy)
  qt_noop();

  // end test

  UI::Application::Application application = UI::Application::Application();

  application.view()->show();

  return a.exec();
}
