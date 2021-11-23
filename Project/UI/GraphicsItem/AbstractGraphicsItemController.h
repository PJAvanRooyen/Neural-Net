#ifndef AbstractGraphicsItemController_H
#define AbstractGraphicsItemController_H

#include <QGraphicsItem>

namespace UI {

class AbstractGraphicsItemController : public QObject {
  Q_OBJECT
public:
  QGraphicsItem *view();

  ~AbstractGraphicsItemController();

protected:
  AbstractGraphicsItemController(QObject *parent = Q_NULLPTR);

  virtual QGraphicsItem *createView(QGraphicsItem *parentView) = 0;

  void setView(QGraphicsItem *view);

private:
  QGraphicsItem *mView;
};

} // namespace UI
#endif // AbstractGraphicsItemController_H
