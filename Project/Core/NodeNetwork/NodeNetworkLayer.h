#ifndef NodeNetworkLayer_H
#define NodeNetworkLayer_H

#include "Shared/NodeNetwork/AbstractNodeNetworkLayer.h"

namespace Core {
namespace NodeNetwork {

class NodeNetworkLayer : public Shared::NodeNetwork::AbstractNodeNetworkLayer {
public:
  NodeNetworkLayer();

  ~NodeNetworkLayer();
};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetworkLayer_H
