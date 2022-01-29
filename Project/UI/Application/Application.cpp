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
      mRightDockWidget(new RightDockWidget(this, this->view())) {
  mView->setCentralWidget(mCentralWidget->view());
  mView->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea,
                       mRightDockWidget->view<RightDockWidgetView>());
}

Application::~Application() { mView->deleteLater(); }

ApplicationView *Application::view() const { return mView; }

} // namespace Application
} // namespace UI
