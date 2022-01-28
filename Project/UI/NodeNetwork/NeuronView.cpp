#include "NeuronView.h"

#include "Shared/NeuralNetwork/Defines.h"

#include <QLabel>
#include <QVBoxLayout>

namespace UI {
namespace NodeNetwork {
NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::NeuronInfoWidget()
    : QWidget(), mActivation(new QLabel(this)), mBias(new QLabel(this)),
      mSensitivity(new QLabel(this)) {
  setLayout(new QVBoxLayout(this));

  mActivation->setFont(QFont("NeuralNetworkData", 5));
  mBias->setFont(QFont("NeuralNetworkData", 5));
  mSensitivity->setFont(QFont("NeuralNetworkData", 5));

  auto *layout = this->layout();
  layout->addWidget(mActivation);
  layout->addWidget(mBias);
  layout->addWidget(mSensitivity);
}

void NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::setData(
    const Shared::NodeNetwork::NeuronData<double> &neuronData) {
  if (neuronData.activation.has_value()) {
    mActivation->setText(QString("A: %1").arg(
        QString::number(neuronData.activation.value(), 'g', 4)));
    mActivation->show();
  } else {
    mActivation->hide();
  }

  mBias->setText(
      QString("B: %1").arg(QString::number(neuronData.bias, 'g', 4)));

  if (neuronData.sensitivity.has_value()) {
    mSensitivity->setText(QString("S: %1").arg(
        QString::number(neuronData.sensitivity.value(), 'g', 4)));
    mSensitivity->show();
  } else {
    mSensitivity->hide();
  }
}

NeuronView::NeuronInfoProxyWidget::NeuronInfoProxyWidget(QGraphicsItem *parent)
    : QGraphicsProxyWidget(parent) {
  setWidget(new NeuronInfoWidget());
  setZValue(std::numeric_limits<int>::max());
}

NeuronView::NeuronInfoProxyWidget::~NeuronInfoProxyWidget() {
  // proxy widget will automatically delete the embedded widget.
}

void NeuronView::NeuronInfoProxyWidget::setData(
    const Shared::NodeNetwork::NeuronData<double> &neuronData) {
  static_cast<NeuronInfoWidget *>(widget())->setData(neuronData);
}

NeuronView::NeuronView(QGraphicsItem *parent)
    : NodeView(parent), mNeuronInfoProxyWidget(this) {
  setZValue(3);
}

void NeuronView::setData(
    const Shared::NodeNetwork::NeuronData<double> &neuronData) {
  mNeuronInfoProxyWidget.setData(neuronData);
}

void NeuronView::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  NodeView::paint(painter, option, widget);
}

} // namespace NodeNetwork
} // namespace UI
