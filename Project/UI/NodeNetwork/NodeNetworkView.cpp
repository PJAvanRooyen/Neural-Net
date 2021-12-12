#include "NodeNetworkView.h"
#include "NodeNetworkLayerView.h"

#include <QPainter>

namespace UI {
namespace NodeNetwork {

const qreal NodeNetworkView::kBorder = 10;
const qreal NodeNetworkView::kLayerOffset = 100;

NodeNetworkView::NodeNetworkView(QGraphicsItem *parent)
    : QGraphicsItem(parent), Shared::NodeNetwork::AbstractNodeNetwork() {}

void NodeNetworkView::repositionLayers() {
  if (mLayers.empty()) {
    return;
  }

  //  // sort by x-position
  //  auto sortByXPos = [](Shared::NodeNetwork::AbstractNodeNetworkLayer
  //  *layer1,
  //                       Shared::NodeNetwork::AbstractNodeNetworkLayer
  //                       *layer2) {
  //    return static_cast<NodeNetworkLayerView *>(layer1)->pos().x() <=
  //           static_cast<NodeNetworkLayerView *>(layer2)->pos().x();
  //  };

  //  std::sort(mLayers.begin(), mLayers.end(), sortByXPos);

  auto layersSize = mLayers.size();
  for (unsigned long layerIdx = 0; layerIdx < layersSize; ++layerIdx) {
    auto *layer = static_cast<NodeNetworkLayerView *>(mLayers.at(layerIdx));
    layer->setPos(layerIdx * kLayerOffset + kBorder, kBorder);
  }
  update();
}

void NodeNetworkView::addLayer(
    Shared::NodeNetwork::AbstractNodeNetworkLayer *layer) {
  AbstractNodeNetwork::addLayer(layer);

  // position layer
  repositionLayers();
}

void NodeNetworkView::addLayers(
    std::vector<Shared::NodeNetwork::AbstractNodeNetworkLayer *> &layers) {
  AbstractNodeNetwork::addLayers(layers);

  // position layers
  repositionLayers();
}

QRectF NodeNetworkView::boundingRect() const {
  if (mLayers.empty()) {
    return QRectF();
  }

  auto firstLayerWidht =
      static_cast<NodeNetworkLayerView *>(mLayers[0])->boundingRect().width();
  auto lastLayerWidht =
      static_cast<NodeNetworkLayerView *>(mLayers[mLayers.size() - 1])
          ->boundingRect()
          .width();
  double width = firstLayerWidht / 2 + lastLayerWidht / 2 +
                 (mLayers.size() - 1) * kLayerOffset;

  double height = 0;
  for (auto *layer : mLayers) {
    auto layerRect = static_cast<NodeNetworkLayerView *>(layer)->boundingRect();
    height = std::max(height, layerRect.height());
  }

  return QRectF(0, 0, width + 2 * kBorder, height + 2 * kBorder);
}

void NodeNetworkView::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  // painter->setPen(Qt::black);
  painter->setBackgroundMode(Qt::BGMode::TransparentMode);
  painter->setBrush(Qt::darkGray);
  painter->drawRect(boundingRect());

  auto *parentItem = this->parentItem();
  if (parentItem)
    parentItem->update();
}

} // namespace NodeNetwork
} // namespace UI
