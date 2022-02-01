#ifndef NeuralNetworkTestWidget_H
#define NeuralNetworkTestWidget_H

#include "UI/ViewController/AbstractViewController.h"

namespace UI {
namespace Application {

class NeuralNetworkTestWidgetView;

class NeuralNetworkTestWidget : public AbstractWidgetController {
  Q_OBJECT

public:
  NeuralNetworkTestWidget(AbstractWidgetController *parent = nullptr);

  // AbstractViewController interface
protected:
  QWidget *createView(QWidget *parentView);
};

} // namespace Application
} // namespace UI
#endif // NeuralNetworkTestWidget_H
