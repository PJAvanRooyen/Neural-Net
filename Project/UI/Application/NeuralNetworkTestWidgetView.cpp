#include "NeuralNetworkTestWidgetView.h"
#include "./ui_NeuralNetworkTestWidget.h"

namespace UI {
namespace Application {

NeuralNetworkTestWidgetView::NeuralNetworkTestWidgetView(QWidget *parent)
    : QWidget(parent), ui(new Ui::NeuralNetworkTestWidget) {
  ui->setupUi(this);
}

NeuralNetworkTestWidgetView::~NeuralNetworkTestWidgetView() { delete ui; };
} // namespace Application
} // namespace UI

void UI::Application::NeuralNetworkTestWidgetView::
    on_mLearningIterationButton_released() {
  // TODO:
  // -move neural network manager to application
  // -connect this to neural network manager
  // -store test data so that a test iteration can independently select a
  // datapoint to run.
  // -let connection send event to run a test iteration
}

void UI::Application::NeuralNetworkTestWidgetView::
    on_mTestIterationButton_released() {}
