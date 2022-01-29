#ifndef NeuralNetworkRunWidgetView_H
#define NeuralNetworkRunWidgetView_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class NeuralNetworkRunWidget;
}
QT_END_NAMESPACE

namespace UI {
namespace Application {

class NeuralNetworkRunWidgetView : public QWidget {
public:
  NeuralNetworkRunWidgetView(QWidget *parent = nullptr);

  ~NeuralNetworkRunWidgetView();

private slots:
  void on_mLearningIterationButton_released();

  void on_mTestIterationButton_released();

private:
  Ui::NeuralNetworkRunWidget *ui;
};

} // namespace Application
} // namespace UI
#endif // NeuralNetworkRunWidgetView_H
