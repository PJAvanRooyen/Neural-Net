#include "RightDockWidget.h"
#include "RightDockWidgetView.h"

#include "UI/Application/NeuralNetworkTestWidget.h"
#include "UI/Application/NeuralNetworkTestWidgetView.h"

namespace UI {
namespace Application {

RightDockWidget::RightDockWidget(QObject *parent, QWidget *parentView)
    : AbstractWidgetController(parent),
      mNeuralNetworkTestWidget(new NeuralNetworkTestWidget(this)) {

  // create view manually when parent is not an AbstractWidgetController
  initView(parentView);

  auto *netTestWidgetView =
      mNeuralNetworkTestWidget->view<NeuralNetworkTestWidgetView>();
  view<RightDockWidgetView>()->setWidget(netTestWidgetView);

  connect(mNeuralNetworkTestWidget,
          &NeuralNetworkTestWidget::runTestButton_released, this,
          &RightDockWidget::runTestButton_released);
}

QWidget *RightDockWidget::createView(QWidget *parentView) {
  return new RightDockWidgetView(parentView);
}

} // namespace Application
} // namespace UI
