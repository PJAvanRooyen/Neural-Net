#include "Node.h"
#include "NodeView.h"

#include <QPainter>
#include <QRectF>

namespace UI {
namespace NodeNetwork {

Node::Node(QObject *parent) : AbstractGraphicsItemController(parent) {}

Node::~Node(){};

void Node::addInputNodeConnection(NodeConnection *nodeConnection) {
  mInputNodeConnections.push_back(nodeConnection);
}

QVector<NodeConnection *> Node::inputNodeConnections() const {
  return mInputNodeConnections;
}

void Node::addOutputNodeConnection(NodeConnection *nodeConnection) {
  mOutputNodeConnections.push_back(nodeConnection);
}

QVector<NodeConnection *> Node::outputNodeConnections() const {
  return mOutputNodeConnections;
}

QVector<NodeConnection *> Node::nodeConnections() const {
  QVector<NodeConnection *> nodeConnections = mInputNodeConnections;
  nodeConnections.append(mOutputNodeConnections);
  return nodeConnections;
}

QGraphicsItem *Node::createView(QGraphicsItem *parentView) {
  return new NodeView(parentView);
}

} // namespace NodeNetwork
} // namespace UI
