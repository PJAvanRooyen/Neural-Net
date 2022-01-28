#include "CentralWidgetView.h"

namespace UI {
namespace Application {

CentralWidgetView::CentralWidgetView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {
  setRenderHint(QPainter::Antialiasing);
  setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  setBackgroundBrush(QColor(230, 200, 167));
  show();
}

} // namespace Application
} // namespace UI
