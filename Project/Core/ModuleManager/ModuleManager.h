#ifndef ModuleManager_H
#define ModuleManager_H
#include "UI/WidgetManager/WidgetManager.h"

namespace Core {
namespace ModuleManager {

class ModuleManager {
public:
  ModuleManager();

  ~ModuleManager();

  UI::WidgetManager::WidgetManager *mWidgetManager;
};

} // namespace ModuleManager
} // namespace Core

#endif // ModuleManager_H
