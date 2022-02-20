#ifndef NeuronView_H
#define NeuronView_H

#include "Shared/NeuralNetwork/Defines.h"
#include "UI/NodeNetwork/NodeView.h"

#include <QGraphicsProxyWidget>
#include <QWidget>

#include <optional>

class QLabel;

namespace UI {
namespace NodeNetwork {

class NeuronView : public NodeView {
  class NeuronInfoProxyWidget : public QGraphicsProxyWidget {
    class NeuronInfoWidget : public QWidget {
      static const QString kDesiredActivationTitle;
      static const QString kActivationTitle;
      static const QString kBiasTitle;
      static const QString kSensitivityTitle;

      static const int kPrecision;
      static const int kFont;

    public:
      NeuronInfoWidget();

      void initLable(QLabel *label);

      void setData(const Shared::NodeNetwork::NeuronData<double> &neuronData);

      QString textForValue(const QString &title,
                           const std::optional<double> previousValue,
                           const double value) const;

    private:
      QLabel *mDesiredActivation;
      QLabel *mActivation;
      QLabel *mBias;
      QLabel *mSensitivity;

      std::optional<Shared::NodeNetwork::NeuronData<double>> mPreviousData;
    };

  public:
    NeuronInfoProxyWidget(QGraphicsItem *parent = nullptr);
    ~NeuronInfoProxyWidget();

    void setData(const Shared::NodeNetwork::NeuronData<double> &neuronData);
  };

public:
  NeuronView(QGraphicsItem *parent = Q_NULLPTR);

  void setData(const Shared::NodeNetwork::NeuronData<double> &neuronData);

  // QGraphicsItem interface
public:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  NeuronInfoProxyWidget mNeuronInfoProxyWidget;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuronView_H
