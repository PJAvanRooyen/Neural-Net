#include "NodeNetworkLayerView.h"

namespace UI {
namespace NodeNetwork {

NodeNetworkLayerView::NodeNetworkLayerView(QGraphicsItem *parent)
    : QGraphicsItem(parent), Shared::NodeNetwork::AbstractNodeNetworkLayer() {}

QRectF NodeNetworkLayerView::boundingRect() const { return QRectF(); }

void NodeNetworkLayerView::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget) {
  Q_UNUSED(painter);
  Q_UNUSED(option);
  Q_UNUSED(widget);
}

// void NodeNetworkLayerView::paint(QPainter *painter,
//                                 const QStyleOptionGraphicsItem *option,
//                                 QWidget *) {
//  Q_UNUSED(painter);
//  Q_UNUSED(option);
//  for (auto *node : mNodes) {
//    node->show();
//  }
//}
} // namespace NodeNetwork
} // namespace UI
