#ifndef CentralWidget_H
#define CentralWidget_H

#include "UI/NodeNetwork/NeuralNetworkManager.h"

#include <QObject>

class QGraphicsScene;

namespace UI {
namespace NodeNetwork {
class NeuralNetwork;
}

namespace Application {

class CentralWidgetView;

class CentralWidget : public QObject {
  Q_OBJECT

public:
  CentralWidget(QObject *parent = nullptr);

  QUuid createTestNetwork();

  void runTest(const QUuid &networkId);

  CentralWidgetView *view() const;

private:
  QGraphicsScene *mScene;
  CentralWidgetView *mView;
  UI::NodeNetwork::NeuralNetworkManager mNetworkManager;
};

} // namespace Application
} // namespace UI
#endif // CentralWidget_H
