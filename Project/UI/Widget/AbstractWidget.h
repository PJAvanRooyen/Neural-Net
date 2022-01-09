#ifndef AbstractWidget_H
#define AbstractWidget_H

#include <QObject>

namespace UI {

class AbstractWidget : public QObject {
  Q_OBJECT
public:
  QWidget *view();

  ~AbstractWidget();

protected:
  AbstractWidget(QObject *parent = Q_NULLPTR);

  virtual QWidget *createView(QWidget *parentView) = 0;

  void setView(QWidget *view);

private:
  QWidget *mView;
};

} // namespace UI
#endif // AbstractWidget_H
