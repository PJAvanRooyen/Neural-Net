#ifndef Application_H
#define Application_H

#include <QWidget>

namespace UI {
namespace Application {

class CentralWidget;
class RightDockWidget;

class ApplicationView;

class Application : public QWidget {
public:
  Application(QWidget *parent = Q_NULLPTR);
  ~Application();

  ApplicationView *view() const;

private:
  ApplicationView *mView;
  CentralWidget *mCentralWidget;
  RightDockWidget *mRightDockWidget;
};

} // namespace Application
} // namespace UI

#endif // Application_H
