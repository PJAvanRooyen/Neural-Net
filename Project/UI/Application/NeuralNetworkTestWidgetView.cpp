#include "NeuralNetworkTestWidgetView.h"
#include "./ui_NeuralNetworkTestWidget.h"

#include "Shared/NeuralNetwork/Defines.h"

namespace UI {
namespace Application {

NeuralNetworkTestWidgetView::NeuralNetworkTestWidgetView(QWidget *parent)
    : QWidget(parent), ui(new Ui::NeuralNetworkTestWidget) {
  ui->setupUi(this);
}

NeuralNetworkTestWidgetView::~NeuralNetworkTestWidgetView() { delete ui; };
} // namespace Application
} // namespace UI

void UI::Application::NeuralNetworkTestWidgetView::on_RunTestButton_released() {

  Shared::NodeNetwork::TestConfiguration testConfig;

  bool ok = false;
  testConfig.learningIterations =
      ui->LearningIterationsLineEdit->text().toULong(&ok);
  if (!ok) {
    ui->LearningIterationsLineEdit->setStatusTip("invalid");
    return;
  }
  testConfig.testingIterations =
      ui->TestIterationsLineEdit->text().toULong(&ok);
  if (!ok) {
    ui->TestIterationsLineEdit->setStatusTip("invalid");
    return;
  }
  testConfig.weightsAndBiasSeed = std::nullopt;
  if (!ui->WeightsSeedRandomizeButton->isChecked()) {
    testConfig.weightsAndBiasSeed.emplace(
        ui->WeightsSeedLineEdit->text().toULong(&ok));
    if (!ok) {
      ui->WeightsSeedLineEdit->setStatusTip("invalid");
      return;
    }
  }
  testConfig.dataSeed = std::nullopt;
  if (!ui->TestDataSeedRandomizeButton->isChecked()) {
    testConfig.dataSeed.emplace(ui->TestDataSeedLineEdit->text().toULong(&ok));
    if (!ok) {
      ui->TestDataSeedLineEdit->setStatusTip("invalid");
      return;
    }
  }
  testConfig.learningRate = ui->LearningRateLineEdit->text().toDouble(&ok);
  if (!ok) {
    ui->LearningRateLineEdit->setStatusTip("invalid");
    return;
  }

  Q_EMIT runTestButton_released(testConfig);
}

void UI::Application::NeuralNetworkTestWidgetView::
    on_WeightsSeedRandomizeButton_released() {
  ui->WeightsSeedLineEdit->setEnabled(
      !ui->WeightsSeedRandomizeButton->isChecked());
}

void UI::Application::NeuralNetworkTestWidgetView::
    on_TestDataSeedRandomizeButton_released() {
  ui->TestDataSeedLineEdit->setEnabled(
      !ui->TestDataSeedRandomizeButton->isChecked());
}
