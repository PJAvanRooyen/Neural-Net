#ifndef NeuralNetworkTestWidgetView_H
#define NeuralNetworkTestWidgetView_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class NeuralNetworkTestWidget;
}
QT_END_NAMESPACE

namespace Shared {
namespace NodeNetwork {
struct TestConfiguration;
}
} // namespace Shared

namespace UI {
namespace Application {

class NeuralNetworkTestWidgetView : public QWidget {
  Q_OBJECT

Q_SIGNALS:
  void runTestButton_released(
      const Shared::NodeNetwork::TestConfiguration &testConfig);

public:
  NeuralNetworkTestWidgetView(QWidget *parent = nullptr);

  ~NeuralNetworkTestWidgetView();

private slots:
  void on_RunTestButton_released();

  void on_WeightsSeedRandomizeButton_released();

  void on_TestDataSeedRandomizeButton_released();

private:
  Ui::NeuralNetworkTestWidget *ui;
};

} // namespace Application
} // namespace UI
#endif // NeuralNetworkTestWidgetView_H
