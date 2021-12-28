#ifndef Neuron_H
#define Neuron_H

#include "Core/NodeNetwork/Node.h"
#include "Core/NodeNetwork/NodeConnection.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <optional>
#include <random>

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

//----------------------------------------------------------------------------
template <typename DataType>
DataType weightFunctionLinear(const DataType input, const DataType weight) {
  return input * weight;
}
//----------------------------------------------------------------------------
template <typename DataType>
DataType biasFunctionConstant(const DataType input, const DataType bias) {
  return input + bias;
}
//----------------------------------------------------------------------------
template <typename DataType>
DataType activationFunctionSigmoid(const DataType input) {
  return DataType(1) / (DataType(1) + std::exp(-input));
}

template <typename DataType>
DataType activationFunctionReLu(const DataType input) {
  return std::max(DataType(0), input);
}
//----------------------------------------------------------------------------
std::default_random_engine randomizer(1);

template <typename DataType>
std::normal_distribution<DataType>
    dist = std::normal_distribution<DataType>(DataType(0.5), DataType(1));

template <typename DataType> class Neuron : public Node {

  typedef DataType (*ActivationFunction)(DataType);

  typedef DataType (*BiasFunction)(DataType, DataType);

public:
  Neuron(const ActivationFunction &activationFunction = activationFunctionReLu,
         const BiasFunction &biasFunction = biasFunctionConstant,
         const DataType initialBias = dist<DataType>(randomizer))
      : Node(), mActivationFunction(activationFunction),
        mBiasFunction(biasFunction), mBias(initialBias) {}

  ~Neuron();

  DataType bias() const { return mBias; }

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

  typedef DataType (*WeightFunction)(DataType, DataType);

public:
  NeuronConnection(Neuron<DataType> *sourceNeuron, Neuron<DataType> *destNeuron,
                   const WeightFunction &weightFunction = weightFunctionLinear,
                   const DataType initialWeight = dist<DataType>(randomizer))
      : NodeConnection(sourceNeuron, destNeuron),
        mWeightFunction(weightFunction), mWeight(initialWeight),
        mInputValue(std::nullopt) {}

  void setInputValue(const DataType inputValue) {
    mInputValue.emplace(inputValue);
  }

  DataType output() const {
    if (!mInputValue.has_value()) {
      return DataType(0);
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
      [](DataType val,
         const Shared::NodeNetwork::AbstractNodeConnection *neuronConnection) {
        return val +
               static_cast<const NeuronConnection<DataType> *>(neuronConnection)
                   ->output();
      };

  DataType connectionOutputSum = std::accumulate(mInputNodeConnections.cbegin(),
                                                 mInputNodeConnections.cend(),
                                                 DataType(0), connectionOutput);

  // normalize the value
  connectionOutputSum /= std::sqrt(mInputNodeConnections.size());

  // pass the sum through this neuron's bias and activation functions.
  const DataType activationValue =
      mActivationFunction(mBiasFunction(connectionOutputSum, mBias));

  // set the input value of all output connections.
  for (auto nodeConnection : mOutputNodeConnections) {
    static_cast<NeuronConnection<DataType> *>(nodeConnection)
        ->setInputValue(activationValue);
  }
}

} // namespace NodeNetwork
} // namespace Core

#endif // Neuron_H
