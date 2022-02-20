#ifndef ApplicationView_H
#define ApplicationView_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace UI {
namespace Application {

class ApplicationView : public QMainWindow {
  Q_OBJECT

public:
  ApplicationView();
  ~ApplicationView();

private:
  Ui::MainWindow *ui;
};

} // namespace Application
} // namespace UI
#endif // ApplicationView_H
