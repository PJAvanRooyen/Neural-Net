#ifndef CentralWidget_H
#define CentralWidget_H

#include "CentralWidgetView.h"

#include <QGraphicsScene>

namespace UI {
namespace Application {

class CentralWidget : public QObject {
  Q_OBJECT

public:
  CentralWidget(QObject *parent = nullptr);

  CentralWidgetView *view() const;

private:
  QGraphicsScene *mScene;
  CentralWidgetView *mView;
};

} // namespace Application
} // namespace UI
#endif // CentralWidget_H
