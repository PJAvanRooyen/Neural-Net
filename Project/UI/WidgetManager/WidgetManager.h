#ifndef WidgetManager_H
#define WidgetManager_H
#include <QtGlobal>

namespace UI {
namespace WidgetManager {

class WidgetManager {
public:
  WidgetManager();
  ~WidgetManager();

  void increment(quint8 &val) const;
};

} // namespace WidgetManager
} // namespace UI

#endif // WidgetManager_H
