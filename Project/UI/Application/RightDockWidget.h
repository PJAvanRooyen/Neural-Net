#ifndef RightDockWidget_H
#define RightDockWidget_H

#include <QWidget>

namespace UI {
namespace Application {

class RightDockWidgetView;

class RightDockWidget : public QWidget {
public:
  RightDockWidget(QWidget *parent = nullptr);

  RightDockWidgetView *view() const;

private:
  RightDockWidgetView *mView;
};

} // namespace Application
} // namespace UI
#endif // RightDockWidget_H
