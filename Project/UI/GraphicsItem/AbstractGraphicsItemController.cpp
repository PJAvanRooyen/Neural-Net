#include "AbstractGraphicsItemController.h"

namespace UI {
AbstractGraphicsItemController::~AbstractGraphicsItemController() {}

AbstractGraphicsItemController::AbstractGraphicsItemController(QObject *parent)
    : QObject(parent), mView(Q_NULLPTR) {}

template <class DerivedView>
void AbstractGraphicsItemController::setView(DerivedView *view) {
  mView = view;
}

QGraphicsItem *AbstractGraphicsItemController::viewBase() {
  if (mView) {
    return mView;
  }

  QGraphicsItem *parentWidgetView = Q_NULLPTR;
  auto *parent = this->parent();
  if (parent) {
    Q_ASSERT(dynamic_cast<AbstractGraphicsItemController *>(parent));
    auto *parentWidget = static_cast<AbstractGraphicsItemController *>(parent);
    if (parentWidget) {
      parentWidgetView = parentWidget->viewBase();
    }
  }
  setView(createViewBase(parentWidgetView));
  return mView;
}
} // namespace UI
