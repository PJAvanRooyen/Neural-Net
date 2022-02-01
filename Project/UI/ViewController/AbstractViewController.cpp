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

AbstractGraphicsItemController::~AbstractGraphicsItemController() {}

AbstractGraphicsItemController::AbstractGraphicsItemController(
    AbstractGraphicsItemController *parent)
    : QObject(parent), AbstractViewController<QGraphicsItem>() {}

AbstractGraphicsItemController::AbstractGraphicsItemController(QObject *parent)
    : QObject(parent), AbstractViewController<QGraphicsItem>() {}

void AbstractGraphicsItemController::initView(QGraphicsItem *parentView) {
  setView(createView(parentView));
}

} // namespace UI
