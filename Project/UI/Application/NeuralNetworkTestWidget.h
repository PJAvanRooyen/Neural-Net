#ifndef NeuralNetworkTestWidget_H
#define NeuralNetworkTestWidget_H

#include "UI/ViewController/AbstractViewController.h"

namespace Shared {
namespace NodeNetwork {
struct TestConfiguration;
}
} // namespace Shared

namespace UI {
namespace Application {

class NeuralNetworkTestWidgetView;

class NeuralNetworkTestWidget : public AbstractWidgetController {
  Q_OBJECT

Q_SIGNALS:
  void runTestButton_released(
      const Shared::NodeNetwork::TestConfiguration &testConfig);

public:
  NeuralNetworkTestWidget(AbstractWidgetController *parent = nullptr);

  // AbstractViewController interface
protected:
  QWidget *createView(QWidget *parentView);
};

} // namespace Application
} // namespace UI
#endif // NeuralNetworkTestWidget_H
