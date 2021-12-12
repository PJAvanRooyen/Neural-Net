#ifndef Neuron_H
#define Neuron_H

#include "Core/NodeNetwork/Node.h"
#include "Core/NodeNetwork/NodeConnection.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <optional>

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

/* Activation Function
   the activation function introduces a nonlinearity which introduces curviture
   into the fitting function so that the function stops being a simple straight
   line.
*/

template <typename DataType>
DataType weightFunctionLinear(const DataType input, const DataType gradient) {
  return input * gradient;
}

template <typename DataType>
DataType biasFunctionConstant(const DataType input, const DataType bias) {
  return input + bias;
}

template <typename DataType>
DataType activationFunctionSigmoid(const DataType input) {
  return DataType(1) / (DataType(1) + std::exp(input));
}

template <typename DataType> class Neuron : public Node {

  typedef DataType (*ActivationFunction)(DataType);

  typedef DataType (*BiasFunction)(DataType);

public:
  Neuron(
      const ActivationFunction &activationFunction = activationFunctionSigmoid,
      const BiasFunction &biasFunction = biasFunctionConstant,
      const DataType initialBias = 1)
      : Node(), mActivationFunction(activationFunction),
        mBiasFunction(biasFunction), mBias(initialBias) {}

  ~Neuron();

  void activate();

private:
  /*
   * \brief function pointer for the activation function.
   */
  ActivationFunction mActivationFunction;

  /*
   * \brief function pointer for the bias function.
   */
  BiasFunction mBiasFunction;

  DataType mBias;
}; // namespace NodeNetwork

template <typename DataType> class NeuronConnection : public NodeConnection {

  typedef DataType (*WeightFunction)(DataType);

public:
  NeuronConnection(Neuron<DataType> *sourceNeuron, Neuron<DataType> *destNeuron,
                   const WeightFunction &weightFunction = weightFunctionLinear,
                   const DataType initialWeight = 1)
      : NodeConnection(sourceNeuron, destNeuron),
        mWeightFunction(weightFunction), mWeight(initialWeight),
        mInputValue(std::nullopt) {}

  ~NeuronConnection();

  void setInputValue(const DataType inputValue) {
    mInputValue.emplace(inputValue);
  }

  DataType output() const {
    if (!mInputValue.hasValue()) {
      return 0;
    }
    return mWeightFunction(mInputValue.value(), mWeight);
  }

private:
  /*
   * \brief function pointer for the weight function.
   */
  WeightFunction mWeightFunction;

  DataType mWeight;

  std::optional<DataType> mInputValue;
};

template <typename DataType> inline void Neuron<DataType>::activate() {

  // sum the output values of all input connections.
  auto connectionOutput =
      [](const NeuronConnection<DataType> *neuronConnection) {
        return neuronConnection->output();
      };

  const DataType connectionOutputSum =
      std::accumulate(mInputNodeConnections.cbegin(),
                      mInputNodeConnections.cend(), 0, connectionOutput);

  // pass the sum through this neuron's bias function.
  const DataType activationValue =
      mActivationFunction(mBiasFunction(connectionOutput, mBias));

  // set the input value of all output connections.
  auto setConnectionInput =
      [activationValue](const NeuronConnection<DataType> *neuronConnection) {
        neuronConnection->setInputValue(activationValue);
      };

  std::for_each(mOutputNodeConnections.begin(), mOutputNodeConnections.end(),
                &setConnectionInput);
}

} // namespace NodeNetwork
} // namespace Core

#endif // Neuron_H
