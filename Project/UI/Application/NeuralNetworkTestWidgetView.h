#ifndef NeuralNetworkTestWidgetView_H
#define NeuralNetworkTestWidgetView_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class NeuralNetworkTestWidget;
}
QT_END_NAMESPACE

namespace UI {
namespace Application {

class NeuralNetworkTestWidgetView : public QWidget {
public:
  NeuralNetworkTestWidgetView(QWidget *parent = nullptr);

  ~NeuralNetworkTestWidgetView();

private slots:
  void on_mLearningIterationButton_released();

  void on_mTestIterationButton_released();

private:
  Ui::NeuralNetworkTestWidget *ui;
};

} // namespace Application
} // namespace UI
#endif // NeuralNetworkTestWidgetView_H
