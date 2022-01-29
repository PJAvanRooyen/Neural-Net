#include "RightDockWidget.h"
#include "RightDockWidgetView.h"

namespace UI {
namespace Application {

RightDockWidget::RightDockWidget(QWidget *parent)
    : QWidget(parent), mView(new RightDockWidgetView(this)) {}

RightDockWidgetView *RightDockWidget::view() const { return mView; }

} // namespace Application
} // namespace UI
