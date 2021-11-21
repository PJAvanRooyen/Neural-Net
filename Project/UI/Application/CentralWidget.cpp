#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include <QComboBox>
#include <QVBoxLayout>

// test
#include "UI/NeuralNet/Neuron/Neuron.h"
// test

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent) : AbstractWidget(parent) {
  auto *view = static_cast<CentralWidgetView *>(this->view());

  UI::Neuron::Neuron *neuron = new UI::Neuron::Neuron(this);
  view->addNeuron(neuron);

  view->addNeuron(neuron);

  auto *combobox = new QComboBox(this->view());
  view->addComboBox(combobox);
}

CentralWidget::~CentralWidget(){};

QWidget *CentralWidget::createView(QWidget *parentView) {
  return new UI::Application::CentralWidgetView(parentView);
}

} // namespace Application
} // namespace UI
