#include "AbstractGraphicsItemController.h"

namespace UI {

QGraphicsItem *AbstractGraphicsItemController::view() {
  if (mView) {
    return mView;
  }

  QGraphicsItem *parentWidgetView = Q_NULLPTR;
  auto *parent = this->parent();
  if (parent) {
    Q_ASSERT(dynamic_cast<AbstractGraphicsItemController *>(parent));
    auto *parentWidget = static_cast<AbstractGraphicsItemController *>(parent);
    if (parentWidget) {
      parentWidgetView = parentWidget->view();
    }
  }
  auto *a = createView(parentWidgetView);
  setView(a);
  return mView;
}

AbstractGraphicsItemController::~AbstractGraphicsItemController() {
  if (mView) {
    delete mView;
  }
}

AbstractGraphicsItemController::AbstractGraphicsItemController(QObject *parent)
    : QObject(parent), mView(Q_NULLPTR) {}

void AbstractGraphicsItemController::setView(QGraphicsItem *view) {
  mView = view;
}
} // namespace UI
