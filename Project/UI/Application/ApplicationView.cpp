#include "ApplicationView.h"
#include "./ui_mainwindow.h"

#include <QComboBox>
#include <QVBoxLayout>

namespace UI {
namespace Application {

ApplicationView::ApplicationView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

ApplicationView::~ApplicationView() { delete ui; }

} // namespace Application
} // namespace UI
