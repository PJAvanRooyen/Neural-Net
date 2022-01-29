#ifndef CentralWidget_H
#define CentralWidget_H

#include "UI/NodeNetwork/NeuralNetworkManager.h"

#include <QWidget>

class QGraphicsScene;

namespace UI {
namespace NodeNetwork {
class NeuralNetwork;
}

namespace Application {

class CentralWidgetView;

class CentralWidget : public QWidget {
  Q_OBJECT

public:
  CentralWidget(QWidget *parent = nullptr);

  CentralWidgetView *view() const;

private:
  QGraphicsScene *mScene;
  CentralWidgetView *mView;
  UI::NodeNetwork::NeuralNetworkManager mNetworkManager;
};

} // namespace Application
} // namespace UI
#endif // CentralWidget_H
