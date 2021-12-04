#ifndef Neuron_H
#define Neuron_H

#include "Core/NodeNetwork/Node.h"

namespace Core {
namespace NodeNetwork {

/*  Weight vs. Bias
    (source:
     https://deepai.org/machine-learning-glossary-and-terms/weight-artificial-neural-network)

    Weights and bias are both learnable parameters inside the network.
    A teachable neural network will randomize both the weight and bias
    values before learning initially begins. As training continues,
    both parameters are adjusted toward the desired values and the correct
   output.

    The two parameters differ in the extent of their influence upon the input
   data.

    Simply, bias represents how far off the predictions are from their intended
   value. Biases make up the difference between the function's output and its
   intended output. A low bias suggest that the network is making more
   assumptions about the form of the output, whereas a high bias value makes
   less assumptions about the form of the output.

    Weights, on the other hand, can be thought of as the strength of the
   connection. Weight affects the amount of influence a change in the input will
   have upon the output. A low weight value will have no change on the input,
   and alternatively a larger weight value will more significantly change the
   output.
*/
template <typename DataType> class Neuron : public Node {
  typedef DataType (*WeightFunction)(DataType);

public:
  Neuron(const WeightFunction &weightFunction, const DataType initialWeight = 1)
      : Node(), mWeightFunction(weightFunction), mGradient(initialWeight) {}

  ~Neuron();

  DataType activate(const DataType input) const {
    return mWeightFunction(input, mGradient);
  }

private:
  /*
   * \brief function pointer for the weight function.
   */
  WeightFunction mWeightFunction;

  DataType mGradient;
};

template <typename DataType>
DataType weightFunctionLinear(const DataType input, const DataType gradient) {
  return input * gradient;
}

} // namespace NodeNetwork
} // namespace Core

#endif // Neuron_H
