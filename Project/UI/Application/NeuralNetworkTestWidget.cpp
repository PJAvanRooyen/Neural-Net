#include "NeuralNetworkTestWidget.h"
#include "NeuralNetworkTestWidgetView.h"

namespace UI {
namespace Application {

NeuralNetworkTestWidget::NeuralNetworkTestWidget(
    AbstractWidgetController *parent)
    : AbstractWidgetController(parent) {}

QWidget *NeuralNetworkTestWidget::createView(QWidget *parentView) {
  return new NeuralNetworkTestWidgetView(parentView);
}

} // namespace Application
} // namespace UI
