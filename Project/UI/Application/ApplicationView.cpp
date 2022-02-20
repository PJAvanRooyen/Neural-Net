#include "ApplicationView.h"
#include "./ui_mainwindow.h"

namespace UI {
namespace Application {

ApplicationView::ApplicationView() : QMainWindow(), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

ApplicationView::~ApplicationView() { delete ui; }

} // namespace Application
} // namespace UI
