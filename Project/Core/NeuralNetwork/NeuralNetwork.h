#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Shared/NodeNetwork/AbstractNodeNetwork.h"

#include <Eigen/Dense>

namespace Core {
namespace NodeNetwork {

class NeuralNetwork {

public:
  NeuralNetwork(unsigned long layerSizes[]);

  template <typename DataType>
  DataType predict(){

  };

protected:
  std::vector<unsigned long> mLayerSizes;
};
} // namespace NodeNetwork
} // namespace Core
#endif // NeuralNetwork_H
