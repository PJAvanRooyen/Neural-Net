#ifndef Application_H
#define Application_H

#include "UI/Application/CentralWidget.h"
#include "UI/Widget/AbstractWidget.h"

namespace UI {
namespace Application {

class Application : public AbstractWidget {
  Q_OBJECT
public:
  Application(QObject *parent = Q_NULLPTR);
  ~Application();

protected:
  QWidget *createView(QWidget *parentView) override;

private:
  CentralWidget *mCentralWidget;
};

} // namespace Application
} // namespace UI

#endif // Application_H
