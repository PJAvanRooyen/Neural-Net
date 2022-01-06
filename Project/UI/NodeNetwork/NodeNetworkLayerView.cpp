#include "NodeNetworkLayerView.h"
#include "NodeView.h"

#include <QPainter>

namespace UI {
namespace NodeNetwork {

const qreal NodeNetworkLayerView::kBorder = 10;
const qreal NodeNetworkLayerView::kNodeOffset = 100;

NodeNetworkLayerView::NodeNetworkLayerView(QGraphicsItem *parent)
    : QGraphicsItem(parent), Shared::NodeNetwork::AbstractNodeNetworkLayer() {}

void NodeNetworkLayerView::repositionNodes() {
  if (mNodes.empty()) {
    return;
  }

  //  // sort by y-position
  //  auto sortByYPos = [](AbstractNode *node1, AbstractNode *node2) {
  //    return static_cast<NodeView *>(node1)->pos().y() <=
  //           static_cast<NodeView *>(node2)->pos().y();
  //  };

  //  std::sort(mNodes.begin(), mNodes.end(), sortByYPos);

  auto nodesSize = mNodes.size();
  for (unsigned long nodeIdx = 0; nodeIdx < nodesSize; ++nodeIdx) {
    auto *node = static_cast<NodeView *>(mNodes.at(nodeIdx));
    auto nodeRect = node->boundingRect();
    node->setPos(nodeRect.width() / 2 + kBorder,
                 nodeRect.height() / 2 + nodeIdx * kNodeOffset + kBorder);
  }
  update();
}

Shared::NodeNetwork::AbstractNode *NodeNetworkLayerView::addNode() {
  auto *node = new NodeView(this);
  this->addNode(node);
  return node;
}

void NodeNetworkLayerView::addNode(Shared::NodeNetwork::AbstractNode *node) {
  AbstractNodeNetworkLayer::addNode(node);

  // position node
  repositionNodes();
}
void NodeNetworkLayerView::addNodes(
    std::vector<Shared::NodeNetwork::AbstractNode *> &nodes) {
  AbstractNodeNetworkLayer::addNodes(nodes);

  // position nodes
  repositionNodes();
}

QRectF NodeNetworkLayerView::boundingRect() const {
  if (mNodes.empty()) {
    return QRectF();
  }
  auto nodesCount = mNodes.size();

  auto firstNodeRect = static_cast<NodeView *>(*mNodes.begin())->boundingRect();

  qreal width = firstNodeRect.width() + 2 * kBorder;
  qreal height =
      firstNodeRect.height() + (nodesCount - 1) * kNodeOffset + 2 * kBorder;

  return QRectF(0, 0, width, height);
}

void NodeNetworkLayerView::paint(QPainter *painter,
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
