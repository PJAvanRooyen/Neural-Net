#include "Core/ModuleManager/ModuleManager.h"
#include "UI/Application/Application.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  UI::Application::Application application = UI::Application::Application();
  application.view()->show();

  Core::ModuleManager::ModuleManager moduleManager =
      Core::ModuleManager::ModuleManager();

  return a.exec();
}
