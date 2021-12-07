#ifndef NodeNetwork_H
#define NodeNetwork_H

#include "Shared/NodeNetwork/AbstractNodeNetwork.h"

namespace Core {
namespace NodeNetwork {

/*
 * A node network can also be a node in a larger node network.
 * A node network has input and output connections, which are the start and end
 * of the network. It further has node network layers between those connections.
 */
class NodeNetwork : public Shared::NodeNetwork::AbstractNodeNetwork {};

} // namespace NodeNetwork
} // namespace Core

#endif // NodeNetwork_H
