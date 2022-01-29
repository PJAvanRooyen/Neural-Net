#include "AbstractViewController.h"

namespace UI {
template <class ViewType>
AbstractViewController<ViewType>::~AbstractViewController() {}

template <class ViewType>
AbstractViewController<ViewType>::AbstractViewController() : mView(Q_NULLPTR) {}

template <class ViewType>
void AbstractViewController<ViewType>::setView(ViewType *view) {
  mView = view;
}

AbstractWidgetController::~AbstractWidgetController() {}

AbstractWidgetController::AbstractWidgetController(
    AbstractWidgetController *parent)
    : QObject(parent), AbstractViewController<QWidget>() {}

AbstractWidgetController::AbstractWidgetController(QObject *parent)
    : QObject(parent), AbstractViewController<QWidget>() {}

void AbstractWidgetController::initView(QWidget *parentView) {
  setView(createView(parentView));
}

} // namespace UI
