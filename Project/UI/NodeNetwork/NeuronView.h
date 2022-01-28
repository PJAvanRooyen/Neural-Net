#ifndef NeuronView_H
#define NeuronView_H

#include "UI/NodeNetwork/NodeView.h"

#include <QGraphicsProxyWidget>
#include <QWidget>

class QLabel;

namespace Shared {
namespace NodeNetwork {
template <typename DataType> class NeuronData;
}
} // namespace Shared

namespace UI {
namespace NodeNetwork {

class NeuronView : public NodeView {
  class NeuronInfoProxyWidget : public QGraphicsProxyWidget {
    class NeuronInfoWidget : public QWidget {
    public:
      NeuronInfoWidget();

      void setData(const Shared::NodeNetwork::NeuronData<double> &neuronData);

    private:
      QLabel *mActivation;
      QLabel *mBias;
      QLabel *mSensitivity;
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
