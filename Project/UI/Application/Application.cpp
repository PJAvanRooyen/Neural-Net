#include "Application.h"
#include "ApplicationView.h"

#include "UI/Application/CentralWidget.h"
#include "UI/Application/CentralWidgetView.h"
#include "UI/Application/RightDockWidget.h"
#include "UI/Application/RightDockWidgetView.h"

namespace UI {
namespace Application {

Application::Application(QWidget *parent)
    : QWidget(parent), mView(new ApplicationView(this)),
      mCentralWidget(new CentralWidget(this)),
      mRightDockWidget(new RightDockWidget(this)) {
  mView->setCentralWidget(mCentralWidget->view());
  mView->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea,
                       mRightDockWidget->view());
}

Application::~Application() {}

ApplicationView *Application::view() const { return mView; }

} // namespace Application
} // namespace UI
