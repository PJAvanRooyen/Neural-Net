#ifndef Application_H
#define Application_H

#include <QObject>

namespace Shared {
namespace NodeNetwork {
struct TestConfiguration;
}
} // namespace Shared

namespace UI {
namespace Application {

class CentralWidget;
class RightDockWidget;

class ApplicationView;

class Application : public QObject {
  Q_OBJECT

public Q_SLOTS:
  void on_runTestButton_released(
      const Shared::NodeNetwork::TestConfiguration &testConfig);

public:
  Application();
  ~Application();

  void runTest(const Shared::NodeNetwork::TestConfiguration &testConfig);

  ApplicationView *view() const;

private:
  ApplicationView *mView;
  CentralWidget *mCentralWidget;
  RightDockWidget *mRightDockWidget;
};

} // namespace Application
} // namespace UI

#endif // Application_H
