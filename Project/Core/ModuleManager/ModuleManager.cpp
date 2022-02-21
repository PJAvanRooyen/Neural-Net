#include "ModuleManager.h"
#include "Examples/VariadicTemplate.h"

namespace Core {
namespace ModuleManager {

ModuleManager::ModuleManager()
    : mWidgetManager(UI::WidgetManager::WidgetManager()) {
  quint8 val = 1;

  mWidgetManager.increment(val);

  QString inputString;
  Example::VariadicTemplate variadicTemplate =
      Example::VariadicTemplate(inputString);
  Q_UNUSED(variadicTemplate)

  qt_noop();
}

ModuleManager::~ModuleManager() {}

} // namespace ModuleManager
} // namespace Core
