#ifndef Application_H
#define Application_H

#include <QObject>

namespace UI {
namespace Application {

class CentralWidget;
class RightDockWidget;

class ApplicationView;

class Application : public QObject {
  Q_OBJECT

public:
  Application();
  ~Application();

  void runTest();

  ApplicationView *view() const;

private:
  ApplicationView *mView;
  CentralWidget *mCentralWidget;
  RightDockWidget *mRightDockWidget;
};

} // namespace Application
} // namespace UI

#endif // Application_H
