#include "CentralWidgetView.h"

#include <QComboBox>
#include <QVBoxLayout>

// test
#include "UI/NeuralNet/Neuron/Neuron.h"
// test

namespace UI {
namespace Application {

CentralWidgetView::CentralWidgetView(QWidget *parent) : QWidget(parent) {

  QHBoxLayout *horizontalLayout = new QHBoxLayout(parent);
  setLayout(horizontalLayout);
}

void CentralWidgetView::addNeuron(Neuron::Neuron *neuron) {
  layout()->addWidget(neuron->view());
}

void CentralWidgetView::addComboBox(QComboBox *comboBox) {
  layout()->addWidget(comboBox);
}

} // namespace Application
} // namespace UI
