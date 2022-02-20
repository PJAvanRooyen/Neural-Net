#include "NeuronView.h"

#include <QLabel>
#include <QVBoxLayout>

namespace UI {
namespace NodeNetwork {
const QString NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::
    kDesiredActivationTitle = "D";
const QString
    NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::kActivationTitle = "A";
const QString NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::kBiasTitle =
    "B";
const QString
    NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::kSensitivityTitle =
        "S";

const int NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::kPrecision = 4;
const int NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::kFont = 8;

NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::NeuronInfoWidget()
    : QWidget(), mDesiredActivation(new QLabel(this)),
      mActivation(new QLabel(this)), mBias(new QLabel(this)),
      mSensitivity(new QLabel(this)), mPreviousData(std::nullopt) {
  setLayout(new QVBoxLayout(this));
  layout()->setContentsMargins(0, 0, 0, 0);

  initLable(mDesiredActivation);
  initLable(mActivation);
  initLable(mBias);
  initLable(mSensitivity);
}

void NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::initLable(
    QLabel *label) {
  label->setFont(QFont("NeuralNetworkData", kFont));
  label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
  auto *layout = this->layout();
  layout->addWidget(label);
}

void NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::setData(
    const Shared::NodeNetwork::NeuronData<double> &neuronData) {
  setBackgroundRole(QPalette::Dark);

  if (neuronData.desiredActivation.has_value()) {
    mDesiredActivation->setText(
        textForValue(kDesiredActivationTitle, std::nullopt,
                     neuronData.desiredActivation.value()));
    mDesiredActivation->show();
  } else {
    mDesiredActivation->hide();
  }

  if (neuronData.activation.has_value()) {
    const auto text = textForValue(kActivationTitle, std::nullopt,
                                   neuronData.activation.value());
    mActivation->setText(text);
    mActivation->show();
  } else {
    mActivation->hide();
  }

  if (neuronData.bias.has_value()) {
    mBias->setText(textForValue(
        kBiasTitle,
        mPreviousData.has_value() ? mPreviousData.value().bias : std::nullopt,
        neuronData.bias.value()));
    mBias->show();
  } else {
    mBias->hide();
  }

  if (neuronData.sensitivity.has_value()) {
    mSensitivity->setText(textForValue(kSensitivityTitle, std::nullopt,
                                       neuronData.sensitivity.value()));
    mSensitivity->show();
  } else {
    mSensitivity->hide();
  }

  setBackgroundRole(QPalette::Light);
  mPreviousData.emplace(neuronData);
}

QString NeuronView::NeuronInfoProxyWidget::NeuronInfoWidget::textForValue(
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
  mNeuronInfoProxyWidget.resize(QSizeF(75, 0));
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
