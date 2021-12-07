#include "NodeNetworkView.h"

namespace UI {
namespace NodeNetwork {

NodeNetworkView::NodeNetworkView(QGraphicsItem *parent)
    : QGraphicsItem(parent), Shared::NodeNetwork::AbstractNodeNetwork() {}

QRectF NodeNetworkView::boundingRect() const { return QRectF(); }

void NodeNetworkView::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(painter);
  Q_UNUSED(option);
  Q_UNUSED(widget);
}

// void NodeNetworkView::paint(QPainter *painter,
//                            const QStyleOptionGraphicsItem *option, QWidget *)
//                            {
//  Q_UNUSED(painter);
//  Q_UNUSED(option);
//  for (auto *layer : mLayers) {
//    layer->show();
//  }
//}

} // namespace NodeNetwork
} // namespace UI
