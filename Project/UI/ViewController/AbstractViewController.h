#ifndef AbstractWidgetController_H
#define AbstractWidgetController_H

#include <QGraphicsItem>
#include <QWidget>

namespace UI {

template <class ViewType> class AbstractViewController {
public:
  template <class DerivedController, class DerivedView>
  DerivedView *view(const QObject *thisDeriviation) {
    if (mView) {
      return static_cast<DerivedView *>(mView);
    }

    ViewType *parentWidgetView = Q_NULLPTR;

    // All derived controllers must also be QObjects.
    QObject *parent = thisDeriviation->parent();
    if (parent) {
      // If this assert fails, then parent is not an AbstractWidgetController.
      // Manually create and set the view on construction using the parent's
      // view.
      Q_ASSERT(dynamic_cast<DerivedController *>(parent));
      auto *parentWidget = static_cast<DerivedController *>(parent);
      if (parentWidget) {
        parentWidgetView = parentWidget->template view<ViewType>();
      }
    }
    DerivedView *view =
        static_cast<DerivedView *>(createView(parentWidgetView));
    setView(view);
    return view;
  }

  ~AbstractViewController();

protected:
  AbstractViewController();

  virtual ViewType *createView(ViewType *parentView) = 0;

  void setView(ViewType *view);

private:
  ViewType *mView;
};

class AbstractWidgetController : public QObject,
                                 AbstractViewController<QWidget> {
  Q_OBJECT
public:
  ~AbstractWidgetController();

  template <class DerivedView> DerivedView *view() {
    return AbstractViewController::view<AbstractWidgetController, DerivedView>(
        this);
  }

protected:
  AbstractWidgetController(AbstractWidgetController *parent);

  // Only use this ctor when the parent is not an AbstractWidgetController.
  // This should be reserved for the highest level items or if the child has a
  // different view type.
  AbstractWidgetController(QObject *parent = Q_NULLPTR);

  // Init is only required if parent is not an AbstractWidgetController.
  // This initialization MUST take place before the view is ever requested.
  void initView(QWidget *parentView);
};

class AbstractGraphicsItemController : public QObject,
                                       AbstractViewController<QGraphicsItem> {
  Q_OBJECT
public:
  ~AbstractGraphicsItemController();

  template <class DerivedView> DerivedView *view() {
    return AbstractViewController::view<AbstractGraphicsItemController,
                                        DerivedView>(this);
  }

  // Init is only required if parent is not an AbstractWidgetController.
  // This initialization MUST take place before the view is ever requested.
  void initView(QGraphicsItem *parentView = Q_NULLPTR);

protected:
  AbstractGraphicsItemController(AbstractGraphicsItemController *parent);

  // Only use this ctor when the parent is not an AbstractWidgetController.
  // This should be reserved for the highest level items or if the child has a
  // different view type.
  AbstractGraphicsItemController(QObject *parent = Q_NULLPTR);
};
} // namespace UI
#endif // AbstractWidgetController_H
