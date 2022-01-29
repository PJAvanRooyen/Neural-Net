#ifndef NeuralNetworkRunWidget_H
#define NeuralNetworkRunWidget_H

#include "UI/ViewController/AbstractViewController.h"

namespace UI {
namespace Application {

class NeuralNetworkRunWidgetView;

class NeuralNetworkRunWidget : public AbstractWidgetController {
  Q_OBJECT

public:
  NeuralNetworkRunWidget(AbstractWidgetController *parent = nullptr);

  // AbstractViewController interface
protected:
  QWidget *createView(QWidget *parentView);
};

} // namespace Application
} // namespace UI
#endif // NeuralNetworkRunWidget_H
