#ifndef RightDockWidget_H
#define RightDockWidget_H

#include "UI/ViewController/AbstractViewController.h"

namespace UI {
namespace Application {

class RightDockWidgetView;
class NeuralNetworkRunWidget;

class RightDockWidget : public AbstractWidgetController {
  Q_OBJECT

public:
  RightDockWidget(QObject *parent, QWidget *parentView);

  // AbstractViewController interface
protected:
  QWidget *createView(QWidget *parentView);

private:
  NeuralNetworkRunWidget *mNeuralNetworkRunWidget;
};

} // namespace Application
} // namespace UI
#endif // RightDockWidget_H
