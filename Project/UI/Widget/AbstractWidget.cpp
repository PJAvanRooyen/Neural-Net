#include "AbstractWidget.h"

#include <QWidget>

namespace UI {

QWidget *AbstractWidget::view() {
  if (mView) {
    return mView;
  }

  QWidget *parentWidgetView = Q_NULLPTR;
  auto *parent = this->parent();
  if (parent) {
    Q_ASSERT(dynamic_cast<AbstractWidget *>(parent));
    auto *parentWidget = static_cast<AbstractWidget *>(parent);
    if (parentWidget) {
      parentWidgetView = parentWidget->view();
    }
  }
  setView(createView(parentWidgetView));
  return mView;
}

AbstractWidget::AbstractWidget(QObject *parent)
    : QObject(parent), mView(Q_NULLPTR) {}

AbstractWidget::~AbstractWidget() {
  if (mView) {
    mView->deleteLater();
  }
};

void AbstractWidget::setView(QWidget *view) { mView = view; }

} // namespace UI
