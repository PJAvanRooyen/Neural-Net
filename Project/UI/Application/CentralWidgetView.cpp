#include "CentralWidgetView.h"

// test
#include "UI/NeuralNet/Neuron/Neuron.h"
// test

namespace UI {
namespace Application {

CentralWidgetView::CentralWidgetView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {
  setRenderHint(QPainter::Antialiasing);
  setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  setBackgroundBrush(QColor(230, 200, 167));
  setWindowTitle("Drag and Drop Robot");
  show();
}

} // namespace Application
} // namespace UI
