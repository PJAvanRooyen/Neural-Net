#include "ModuleManager.h"
#include "Examples/VariadicTemplate.h"

namespace Core {
namespace ModuleManager {

ModuleManager::ModuleManager()
    : mWidgetManager(new UI::WidgetManager::WidgetManager()) {
  quint8 val = 1;

  mWidgetManager->increment(val);

  QString inputString;
  Example::VariadicTemplate variadicTemplate =
      Example::VariadicTemplate(inputString);
  Q_UNUSED(variadicTemplate)

  qt_noop();
}

ModuleManager::~ModuleManager() { delete mWidgetManager; }

} // namespace ModuleManager
} // namespace Core
