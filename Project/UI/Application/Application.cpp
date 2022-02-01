#include "Application.h"
#include "ApplicationView.h"

#include "UI/Application/CentralWidget.h"
#include "UI/Application/CentralWidgetView.h"
#include "UI/Application/RightDockWidget.h"
#include "UI/Application/RightDockWidgetView.h"

namespace UI {
namespace Application {

Application::Application()
    : QObject(), mView(new ApplicationView()),
      mCentralWidget(new CentralWidget(this)),
      mRightDockWidget(new RightDockWidget(this, mView)) {
  mView->showFullScreen();
  mView->setCentralWidget(mCentralWidget->view());
  mView->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea,
                       mRightDockWidget->view<RightDockWidgetView>());
  mView->show();
}

Application::~Application() { mView->deleteLater(); }

void Application::runTest() {
  const QUuid &networkId = mCentralWidget->createTestNetwork();
  mView->repaint();
  mCentralWidget->runTest(networkId);
}

ApplicationView *Application::view() const { return mView; }

} // namespace Application
} // namespace UI
