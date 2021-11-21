#ifndef NeuronView_H
#define NeuronView_H

#include <QWidget>

namespace UI {
namespace Neuron {

class NeuronView : public QWidget {
  Q_OBJECT

public:
  NeuronView(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *event);

private:
};

} // namespace Neuron
} // namespace UI
#endif // NeuronView_H
