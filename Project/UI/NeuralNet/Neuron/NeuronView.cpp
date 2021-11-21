#include "NeuronView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace Neuron {

NeuronView::NeuronView(QWidget *parent) : QWidget(parent) {}

void NeuronView::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)

  QRectF rectangle(100.0, 100.0, 100.0, 100.0);

  QPainter painter(this);

  //  QColor c = QColor();
  //  c.setBlue(100);
  //  painter.setBrush(QBrush(c, Qt::BrushStyle::BDiagPattern));

  //  QPen pen;
  //  pen.setWidth(8);
  //  pen.setBrush(Qt::SolidPattern);
  //  painter.setPen(pen);

  painter.drawEllipse(rectangle);
}
} // namespace Neuron
} // namespace UI
