#ifndef NodeNetworkLayerUI_H
#define NodeNetworkLayerUI_H

#include <QVector>

namespace UI {
namespace NodeNetwork {

class Node;

class NodeNetworkLayer {
public:
  NodeNetworkLayer();

  ~NodeNetworkLayer();

  QVector<Node *> nodes() const;

private:
  QVector<Node *> mNodes;
};

} // namespace NodeNetwork
} // namespace UI

#endif // NodeNetworkLayerUI_H
