#ifndef RightDockWidget_H
#define RightDockWidget_H

#include "UI/ViewController/AbstractViewController.h"

namespace UI {
namespace Application {

class RightDockWidgetView;
class NeuralNetworkTestWidget;

class RightDockWidget : public AbstractWidgetController {
  Q_OBJECT

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
