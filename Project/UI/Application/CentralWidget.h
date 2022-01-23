#ifndef CentralWidget_H
#define CentralWidget_H

#include "CentralWidgetView.h"
#include "UI/NodeNetwork/NeuralNetworkManager.h"

#include <QGraphicsScene>

namespace UI {
namespace Application {

class CentralWidget : public QObject {
  Q_OBJECT

public:
  CentralWidget(QObject *parent = nullptr);

  CentralWidgetView *view() const;

  bool createMeshNetwork(const std::vector<unsigned long> &layerSizes);

private:
  QGraphicsScene *mScene;
  CentralWidgetView *mView;
  UI::NodeNetwork::NeuralNetworkManager mNetworkManager;
};

} // namespace Application
} // namespace UI
#endif // CentralWidget_H
