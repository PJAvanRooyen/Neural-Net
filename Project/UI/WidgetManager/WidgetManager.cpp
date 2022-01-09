#include "WidgetManager.h"

namespace UI {
namespace WidgetManager {

WidgetManager::WidgetManager() {}

WidgetManager::~WidgetManager() {}

void WidgetManager::increment(quint8 &val) const {
  ++val;
  return;
}

} // namespace WidgetManager
} // namespace UI
