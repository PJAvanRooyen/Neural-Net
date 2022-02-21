#include "Application.h"
#include "ApplicationView.h"

#include "UI/Application/CentralWidget.h"
#include "UI/Application/CentralWidgetView.h"
#include "UI/Application/RightDockWidget.h"
#include "UI/Application/RightDockWidgetView.h"

namespace UI {
namespace Application {

void Application::on_runTestButton_released(
    const Shared::NodeNetwork::TestConfiguration &testConfig) {
  runTest(testConfig);
}

Application::Application()
    : QObject(), mView(new ApplicationView()),
      mCentralWidget(new CentralWidget(this)),
      mRightDockWidget(new RightDockWidget(this, mView)) {
  mView->showFullScreen();
  mView->setCentralWidget(mCentralWidget->view());
  mView->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea,
                       mRightDockWidget->view<RightDockWidgetView>());
  mView->show();

  connect(mRightDockWidget, &RightDockWidget::runTestButton_released, this,
          &Application::on_runTestButton_released);
}

Application::~Application() { mView->deleteLater(); }

void Application::runTest(
    const Shared::NodeNetwork::TestConfiguration &testConfig) {

  QUuid networkId;
  const auto &availableNetworks = mCentralWidget->availableNetworks();
  if (availableNetworks.isEmpty()) {
    const std::vector<unsigned long> layerSizes = {4, 30, 30, 30, 3};

    networkId = mCentralWidget->createTestNetwork(
        layerSizes, testConfig.weightsAndBiasSeed, testConfig.learningRate);
  } else {
    networkId = availableNetworks.first();
  }

  mCentralWidget->runTest(networkId, testConfig.learningIterations,
                          testConfig.testingIterations, testConfig.dataSeed);
}

ApplicationView *Application::view() const { return mView; }

} // namespace Application
} // namespace UI
