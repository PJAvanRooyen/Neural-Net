#ifndef RightDockWidget_H
#define RightDockWidget_H

#include "UI/ViewController/AbstractViewController.h"

namespace Shared {
namespace NodeNetwork {
struct TestConfiguration;
}
} // namespace Shared

namespace UI {
namespace Application {

class RightDockWidgetView;
class NeuralNetworkTestWidget;

class RightDockWidget : public AbstractWidgetController {
  Q_OBJECT

Q_SIGNALS:
  void runTestButton_released(
      const Shared::NodeNetwork::TestConfiguration &testConfig);

public:
  RightDockWidget(QObject *parent, QWidget *parentView);

  // AbstractViewController interface
protected:
  QWidget *createView(QWidget *parentView);

private:
  NeuralNetworkTestWidget *mNeuralNetworkTestWidget;
};

} // namespace Application
} // namespace UI
#endif // RightDockWidget_H
