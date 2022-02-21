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

  QList<QUuid> availableNetworks() const;

  QUuid createTestNetwork(const std::vector<unsigned long> &layerSizes,
                          const std::optional<unsigned> seed = std::nullopt,
                          const double learningRate = 0.01);

  void runTest(const QUuid &networkId, const ulong learningIterations,
               const ulong testingIterations,
               const std::optional<ulong> dataSeed = std::nullopt);

  CentralWidgetView *view() const;

private:
  QGraphicsScene *mScene;
  CentralWidgetView *mView;
  UI::NodeNetwork::NeuralNetworkManager mNetworkManager;
};

} // namespace Application
} // namespace UI
#endif // CentralWidget_H
