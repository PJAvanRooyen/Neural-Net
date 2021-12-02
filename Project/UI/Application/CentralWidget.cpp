#include "CentralWidget.h"
#include "CentralWidgetView.h"

#include "NeuralNet/Neuron/Neuron.h"

namespace UI {
namespace Application {

CentralWidget::CentralWidget(QObject *parent)
    : mScene(new QGraphicsScene(parent)), mView(new CentralWidgetView(mScene)) {

  addNeuron();
}

CentralWidgetView *CentralWidget::view() const { return mView; }

void CentralWidget::addNeuron() {
  auto *neuron = new UI::Neuron::Neuron();
  mScene->addItem(neuron->view());
}

} // namespace Application
} // namespace UI