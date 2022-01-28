#ifndef AbstractGraphicsItemController_H
#define AbstractGraphicsItemController_H

#include <QGraphicsItem>

namespace UI {

class AbstractGraphicsItemController : public QObject {
  Q_OBJECT
public:
  template <class DerivedView> DerivedView *view() {
    if (mView) {
      return static_cast<DerivedView *>(mView);
    }

    QGraphicsItem *parentWidgetView = Q_NULLPTR;
    auto *parent = this->parent();
    if (parent) {
      Q_ASSERT(dynamic_cast<AbstractGraphicsItemController *>(parent));
      auto *parentWidget =
          static_cast<AbstractGraphicsItemController *>(parent);
      if (parentWidget) {
        parentWidgetView = parentWidget->viewBase();
      }
    }
    setView(static_cast<QGraphicsItem *>(
        createView<DerivedView>(parentWidgetView)));
    return static_cast<DerivedView *>(mView);
  }

  QGraphicsItem *getView() const { return mView; }

  ~AbstractGraphicsItemController();

protected:
  AbstractGraphicsItemController(QObject *parent = Q_NULLPTR);

  QGraphicsItem *viewBase();

  virtual QGraphicsItem *createViewBase(QGraphicsItem *parentView) = 0;

  template <class DerivedView>
  DerivedView *createView(QGraphicsItem *parentView) {
    return static_cast<DerivedView *>(createViewBase(parentView));
  }

  template <class DerivedView> void setView(DerivedView *view);

private:
  QGraphicsItem *mView;
}; // namespace UI

} // namespace UI
#endif // AbstractGraphicsItemController_H
