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

  view<RightDockWidgetView>()->setWidget(
      mNeuralNetworkTestWidget->view<NeuralNetworkTestWidgetView>());
}

QWidget *RightDockWidget::createView(QWidget *parentView) {
  return new RightDockWidgetView(parentView);
}

} // namespace Application
} // namespace UI
