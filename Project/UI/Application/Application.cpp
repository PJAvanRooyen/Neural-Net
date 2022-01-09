#include "Application.h"
#include "ApplicationView.h"

#include <QWidget>

namespace UI {
namespace Application {

Application::Application(QObject *parent)
    : AbstractWidget(parent), mCentralWidget(new CentralWidget(this)) {
  auto view = static_cast<ApplicationView *>(this->view());
  view->setCentralWidget(mCentralWidget->view());
}

Application::~Application() {}

QWidget *Application::createView(QWidget *parentView) {
  return new ApplicationView(parentView);
}

} // namespace Application
} // namespace UI
