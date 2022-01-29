#include "NeuronConnectionView.h"
#include "NeuronView.h"

#include "Shared/NeuralNetwork/Defines.h"

#include <QLabel>
#include <QVBoxLayout>

namespace UI {
namespace NodeNetwork {
const QString NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::kActivationTitle = "A";
const QString NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::kWeightTitle = "W";

const int NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::kPrecision = 4;
const int NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::kFont = 8;

NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::NeuronConnectionInfoWidget()
    : QWidget(), mActivation(new QLabel(this)), mWeight(new QLabel(this)),
      mPreviousData(std::nullopt) {
  setLayout(new QVBoxLayout(this));
  layout()->setContentsMargins(0, 0, 0, 0);

  mActivation->setFont(QFont("NeuralNetworkData", kFont));
  mWeight->setFont(QFont("NeuralNetworkData", kFont));

  auto *layout = this->layout();
  layout->addWidget(mActivation);
  layout->addWidget(mWeight);
}

void NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::setData(
        const Shared::NodeNetwork::NeuronConnectionData<double>
            &connectionData) {

  if (mPreviousData.has_value()) {
    const auto &previousData = mPreviousData.value();
    if (connectionData.activation.has_value()) {
      mActivation->setText(textForValue(kActivationTitle,
                                        previousData.activation,
                                        connectionData.activation.value()));
      mActivation->show();
    } else {
      mActivation->hide();
    }
    mWeight->setText(
        textForValue(kWeightTitle, previousData.weight, connectionData.weight));
  } else {
    if (connectionData.activation.has_value()) {
      mActivation->setText(textForValue(kActivationTitle, std::nullopt,
                                        connectionData.activation.value()));
      mActivation->show();
    } else {
      mActivation->hide();
    }
    mWeight->setText(
        textForValue(kWeightTitle, std::nullopt, connectionData.weight));
  }

  mPreviousData.emplace(connectionData);
}

QString NeuronConnectionView::NeuronConnectionInfoProxyWidget::
    NeuronConnectionInfoWidget::textForValue(
        const QString &title, const std::optional<double> previousValue,
        const double value) const {
  const bool hasPreviousVal = previousValue.has_value();

  if (!hasPreviousVal) {
    return QString("%1: %2").arg(title,
                                 QString::number(value, 'g', kPrecision));
  } else {
    return QString("%1: %2\n-> %3")
        .arg(title, QString::number(previousValue.value(), 'g', kPrecision),
             QString::number(value, 'g', kPrecision));
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
