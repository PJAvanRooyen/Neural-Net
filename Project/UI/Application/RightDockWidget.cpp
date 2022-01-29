#include "RightDockWidget.h"
#include "RightDockWidgetView.h"

#include "UI/Application/NeuralNetworkRunWidget.h"
#include "UI/Application/NeuralNetworkRunWidgetView.h"

namespace UI {
namespace Application {

RightDockWidget::RightDockWidget(QObject *parent, QWidget *parentView)
    : AbstractWidgetController(parent),
      mNeuralNetworkRunWidget(new NeuralNetworkRunWidget(this)) {

  // create view manually when parent is not an AbstractWidgetController
  initView(parentView);

  view<RightDockWidgetView>()->setWidget(
      mNeuralNetworkRunWidget->view<NeuralNetworkRunWidgetView>());
}

QWidget *RightDockWidget::createView(QWidget *parentView) {
  return new RightDockWidgetView(parentView);
}

} // namespace Application
} // namespace UI
