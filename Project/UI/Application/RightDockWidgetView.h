#ifndef RightDockWidgetView_H
#define RightDockWidgetView_H

#include <QDockWidget>

namespace UI {
namespace Application {

class RightDockWidgetView : public QDockWidget {
  Q_OBJECT

public:
  RightDockWidgetView(QWidget *parent = nullptr);
};

} // namespace Application
} // namespace UI
#endif // RightDockWidgetView_H
