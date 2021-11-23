#ifndef CentralWidgetView_H
#define CentralWidgetView_H

#include <QGraphicsView>

namespace UI {
namespace Application {

class CentralWidgetView : public QGraphicsView {
  Q_OBJECT

public:
  CentralWidgetView(QGraphicsScene *scene = nullptr, QWidget *parent = nullptr);
};

} // namespace Application
} // namespace UI
#endif // CentralWidgetView_H
