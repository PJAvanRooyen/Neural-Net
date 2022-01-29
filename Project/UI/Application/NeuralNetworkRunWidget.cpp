#include "NeuralNetworkRunWidget.h"
#include "NeuralNetworkRunWidgetView.h"

namespace UI {
namespace Application {

NeuralNetworkRunWidget::NeuralNetworkRunWidget(AbstractWidgetController *parent)
    : AbstractWidgetController(parent) {}

QWidget *NeuralNetworkRunWidget::createView(QWidget *parentView) {
  return new NeuralNetworkRunWidgetView(parentView);
}

} // namespace Application
} // namespace UI
