#include "NeuronConnectionView.h"
#include "NeuronView.h"

#include "Shared/NeuralNetwork/Defines.h"

#include <QLabel>
#include <QVBoxLayout>

namespace UI {
namespace NodeNetwork {
NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::NeuronConnectionInfoWidget()
    : QWidget(), mActivation(new QLabel(this)), mWeight(new QLabel(this)) {
  setLayout(new QVBoxLayout(this));

  mActivation->setFont(QFont("NeuralNetworkData", 5));
  mWeight->setFont(QFont("NeuralNetworkData", 5));

  auto *layout = this->layout();
  layout->addWidget(mActivation);
  layout->addWidget(mWeight);
}

void NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::setData(
        const Shared::NodeNetwork::NeuronConnectionData<double>
            &connectionData) {
  if (connectionData.activation.has_value()) {
    mActivation->setText(QString("A: %1").arg(
        QString::number(connectionData.activation.value(), 'g', 4)));
    mActivation->show();
  } else {
    mActivation->hide();
  }

  mWeight->setText(
      QString("W: %1").arg(QString::number(connectionData.weight, 'g', 4)));
  mWeight->show();

  if (connectionData.activation.has_value()) {
    setToolTip(
        QString("A: %1\nW: %2")
            .arg(QString::number(connectionData.activation.value(), 'g', 4),
                 QString::number(connectionData.weight, 'g', 4)));
  } else {
    setToolTip(
        QString("W: %1").arg(QString::number(connectionData.weight, 'g', 4)));
  }
}

NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoProxyWidget(QGraphicsItem *parent)
    : QGraphicsProxyWidget(parent) {
  setWidget(new NeuronConnectionInfoWidget());
  setZValue(std::numeric_limits<int>::max());
}

NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    ~NeuronConnectionInfoProxyWidget() {
  // proxy widget will automatically delete the embedded widget.
}

void NeuronConnectionView::NeuronConnectionInfoProxyWidget::setData(
    const Shared::NodeNetwork::NeuronConnectionData<double> &connectionData) {
  static_cast<NeuronConnectionInfoWidget *>(widget())->setData(connectionData);
}

NeuronConnectionView::NeuronConnectionView(NeuronView *sourceNodeView,
                                           NeuronView *destinationNodeView,
                                           QGraphicsItem *parent)
    : NodeConnectionView(sourceNodeView, destinationNodeView, parent),
      mNeuronConnectionInfoProxyWidget(this) {
  adjust();
  setZValue(3);
}

NeuronConnectionView::~NeuronConnectionView() {}

void NeuronConnectionView::adjust() {
  NodeConnectionView::adjust();

  const auto pos =
      QLineF(mSourcePoint, QLineF(mSourcePoint, mDestinationPoint).center())
          .center();
  mNeuronConnectionInfoProxyWidget.setPos(pos);
}

void NeuronConnectionView::setData(
    const Shared::NodeNetwork::NeuronConnectionData<double> &connectionData) {
  mNeuronConnectionInfoProxyWidget.setData(connectionData);
}

void NeuronConnectionView::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget) {
  NodeConnectionView::paint(painter, option, widget);
}

} // namespace NodeNetwork
} // namespace UI
