#ifndef NeuronConnectionView_H
#define NeuronConnectionView_H

#include "UI/NodeNetwork/NodeConnectionView.h"

#include <QGraphicsProxyWidget>
#include <QWidget>

class QLabel;

namespace Shared {
namespace NodeNetwork {
template <typename DataType> class NeuronConnectionData;
}
} // namespace Shared

namespace UI {
namespace NodeNetwork {

class NeuronView;

class NeuronConnectionView : public NodeConnectionView {
  class NeuronConnectionInfoProxyWidget : public QGraphicsProxyWidget {
    class NeuronConnectionInfoWidget : public QWidget {
    public:
      NeuronConnectionInfoWidget();

      void setData(const Shared::NodeNetwork::NeuronConnectionData<double>
                       &connectionData);

    private:
      QLabel *mActivation;
      QLabel *mWeight;
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
