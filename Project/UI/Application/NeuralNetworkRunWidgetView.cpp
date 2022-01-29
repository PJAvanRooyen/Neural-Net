#include "NeuralNetworkRunWidgetView.h"
#include "./ui_NeuralNetworkRunWidget.h"

namespace UI {
namespace Application {

NeuralNetworkRunWidgetView::NeuralNetworkRunWidgetView(QWidget *parent)
    : QWidget(parent), ui(new Ui::NeuralNetworkRunWidget) {
  ui->setupUi(this);
}

NeuralNetworkRunWidgetView::~NeuralNetworkRunWidgetView() { delete ui; };
} // namespace Application
} // namespace UI

void UI::Application::NeuralNetworkRunWidgetView::
    on_mLearningIterationButton_released() {
  // TODO:
  // -move neural network manager to application
  // -connect this to neural network manager
  // -store test data so that a test iteration can independently select a
  // datapoint to run.
  // -let connection send event to run a test iteration
}

void UI::Application::NeuralNetworkRunWidgetView::
    on_mTestIterationButton_released() {}
