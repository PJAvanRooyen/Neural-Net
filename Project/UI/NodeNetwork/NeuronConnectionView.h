#ifndef NeuronConnectionView_H
#define NeuronConnectionView_H

#include "Shared/NeuralNetwork/Defines.h"
#include "UI/NodeNetwork/NodeConnectionView.h"

#include <QGraphicsProxyWidget>
#include <QWidget>

class QLabel;

namespace UI {
namespace NodeNetwork {

class NeuronView;

class NeuronConnectionView : public NodeConnectionView {
  class NeuronConnectionInfoProxyWidget : public QGraphicsProxyWidget {
    class NeuronConnectionInfoWidget : public QWidget {
      static const QString kActivationTitle;
      static const QString kWeightTitle;

      static const int kPrecision;
      static const int kFont;

    public:
      NeuronConnectionInfoWidget();

      void setData(const Shared::NodeNetwork::NeuronConnectionData<double>
                       &connectionData);

      QString textForValue(const QString &title,
                           const std::optional<double> previousValue,
                           const double value) const;

    private:
      QLabel *mActivation;
      QLabel *mWeight;

      std::optional<Shared::NodeNetwork::NeuronConnectionData<double>>
          mPreviousData;
    };

  public:
    NeuronConnectionInfoProxyWidget(QGraphicsItem *parent = nullptr);
    ~NeuronConnectionInfoProxyWidget();

    void setData(const Shared::NodeNetwork::NeuronConnectionData<double>
                     &connectionData);
  };

public:
  NeuronConnectionView(NeuronView *sourceNodeView,
                       NeuronView *destinationNodeView,
                       QGraphicsItem *parent = Q_NULLPTR);

  ~NeuronConnectionView();

  void setData(
      const Shared::NodeNetwork::NeuronConnectionData<double> &connectionData);

  // QGraphicsItem interface
public:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  void adjust() override;

  NeuronConnectionInfoProxyWidget mNeuronConnectionInfoProxyWidget;
};

} // namespace NodeNetwork
} // namespace UI
#endif // NeuronConnectionView_H
