#include "NeuralNetworkTestWidget.h"
#include "NeuralNetworkTestWidgetView.h"

namespace UI {
namespace Application {

NeuralNetworkTestWidget::NeuralNetworkTestWidget(
    AbstractWidgetController *parent)
    : AbstractWidgetController(parent) {}

QWidget *NeuralNetworkTestWidget::createView(QWidget *parentView) {
  auto *view = new NeuralNetworkTestWidgetView(parentView);
  connect(view, &NeuralNetworkTestWidgetView::runTestButton_released, this,
          &NeuralNetworkTestWidget::runTestButton_released);

  return view;
}

} // namespace Application
} // namespace UI
