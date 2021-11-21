#ifndef CentralWidgetView_H
#define CentralWidgetView_H

#include <QWidget>

// test
#include <QComboBox>
// test

namespace UI {
namespace Neuron {
class Neuron;
}

namespace Application {

class CentralWidgetView : public QWidget {
  Q_OBJECT

public:
  CentralWidgetView(QWidget *parent = nullptr);

  void addNeuron(Neuron::Neuron *neuronView);

  void addComboBox(QComboBox *comboBox);

private:
};

} // namespace Application
} // namespace UI
#endif // CentralWidgetView_H
