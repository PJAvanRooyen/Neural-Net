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

// ___WEIGHT FUNCTIONS___
//----------------------------------------------------------------------------
template <typename DataType>
DataType LinearScale(const DataType input, const DataType weight) {
  return input * weight;
}
//----------------------------------------------------------------------------

// ___BIAS FUNCTIONS___
//----------------------------------------------------------------------------
template <typename DataType>
DataType constantOffset(const DataType input, const DataType bias) {
  return input + bias;
}
//----------------------------------------------------------------------------

// ___ACTIVATION FUNCTIONS___
//----------------------------------------------------------------------------
template <typename DataType> DataType sigmoid(const DataType input) {
  return DataType(1) / (DataType(1) + std::exp(-input));
}
template <typename DataType> DataType sigmoidDerivative(const DataType input) {
  return input * (DataType(1) - input);
}

template <typename DataType> DataType reLu(const DataType input) {
  return std::max(DataType(0), input);
}
template <typename DataType> DataType reLuDerivative(const DataType) {
  return DataType(1);
}
//----------------------------------------------------------------------------

// ___COST FUNCTIONS___
//----------------------------------------------------------------------------
template <typename DataType>
DataType error(const DataType output, const DataType desiredOutput) {
  return output - desiredOutput;
}

template <typename DataType>
DataType squareError(const DataType output, const DataType desiredOutput) {
  return std::pow(output - desiredOutput, 2);
}
// ___COST FUNCTION DERIVATIVE dC/dA___
// where C is the cost, and A is the activation value
template <typename DataType>
DataType squareErrorDerivative(const DataType output,
                               const DataType desiredOutput) {
  return 2 * (output - desiredOutput);
}
//----------------------------------------------------------------------------

// ___LEARNING RATE___
//----------------------------------------------------------------------------
double kLearningRate = 0.1;
//----------------------------------------------------------------------------

// ___RANDOMIZATION FUNCTIONS___
//----------------------------------------------------------------------------
std::default_random_engine randomizer(1);

template <typename DataType>
std::normal_distribution<DataType>
    kNormalDist = std::normal_distribution<DataType>(DataType(0), DataType(1));
//----------------------------------------------------------------------------

template <typename DataType> class Neuron : public Node {

  typedef DataType (*ActivationFunction)(const DataType);

  typedef DataType (*BiasFunction)(const DataType, const DataType);

  typedef DataType (*CostFunction)(const DataType, const DataType);

public:
  Neuron()
      : Node(), mBiasFunction(constantOffset),
        mBias(kNormalDist<DataType>(randomizer)), mActivationFunction(reLu),
        mActivation(std::nullopt) {}

  ~Neuron();

  DataType bias() const { return mBias; }

  DataType value() {
    if (mActivation.has_value()) {
      return mActivation.value();
    }
    return activate();
  }

  void setBias(const DataType bias) { mBias = bias; }

  void setValue(const DataType value) { mActivation.emplace(value); }

  DataType activate();

  void backPropagate(const DataType desiredActivation);

private:
  /*
   * \brief function pointer for the bias function.
   */
  BiasFunction mBiasFunction;

  DataType mBias;

  /*
   * \brief function pointer for the activation function.
   */
  ActivationFunction mActivationFunction;

  std::optional<DataType> mActivation;
}; // namespace NodeNetwork

template <typename DataType> class NeuronConnection : public NodeConnection {

  typedef DataType (*WeightFunction)(DataType, DataType);

public:
  NeuronConnection(Neuron<DataType> *sourceNeuron, Neuron<DataType> *destNeuron)
      : NodeConnection(sourceNeuron, destNeuron), mWeightFunction(LinearScale),
        mWeight(kNormalDist<DataType>(randomizer)), mActivation(std::nullopt) {}

  DataType weight() const { return mWeight; }

  void setWeight(const DataType weight) { mWeight = weight; }

  DataType value() {
    if (mActivation.has_value()) {
      return mActivation.value();
    }
    return activate();
  }

  DataType activate() {
    Neuron<DataType> *sourceNeuron = static_cast<Neuron<DataType> *>(mSource);
    mActivation.emplace(mWeightFunction(sourceNeuron->activate(), mWeight));

    return mActivation.value();
  }

  void backPropagate(const DataType desiredOutput) {
    // back propagate

    mActivation.reset();
  }

private:
  /*
   * \brief function pointer for the weight function.
   */
  WeightFunction mWeightFunction;

  DataType mWeight;

  std::optional<DataType> mActivation;
};

template <typename DataType> inline DataType Neuron<DataType>::activate() {
  if (mInputNodeConnections.size() == 0) {
    if (mActivation.has_value()) {
      return mActivation.value();
    } else {
      return DataType(0);
    }
  }

  // sum the output values of all input connections.
  auto connectionOutput =
      [](const DataType val,
         Shared::NodeNetwork::AbstractNodeConnection *neuronConnection) {
        return val + static_cast<NeuronConnection<DataType> *>(neuronConnection)
                         ->activate();
      };

  DataType connectionOutputSum = std::accumulate(mInputNodeConnections.cbegin(),
                                                 mInputNodeConnections.cend(),
                                                 DataType(0), connectionOutput);
  // normalize the value
  connectionOutputSum /=
      mInputNodeConnections.size();

  // pass the sum through this neuron's bias function.
  const DataType biasedSum = mBiasFunction(connectionOutputSum, mBias);

  // pass the sum through this neuron's activation function.
  mActivation.emplace(mActivationFunction(biasedSum));

  return mActivation.value();
}

template <typename DataType>
inline void Neuron<DataType>::backPropagate(const DataType desiredActivation) {
  //  DataType normConnectionOutputSum = mConnectionOutputSum;
  //  if (mInputNodeConnections.size() != 0) {
  //    normConnectionOutputSum /= std::sqrt(mInputNodeConnections.size());
  //  }

  //  const DataType desiredBias = desiredActivation - normConnectionOutputSum;
  //  mBias -= kLearningRate * (mBias - desiredBias);

  //  DataType desiredConnectionSum = (desiredActivation - mBias) *
  //  std::sqrt(2);

  //  for (auto nodeConnection : mInputNodeConnections) {
  //    auto *neuronConnection =
  //        static_cast<NeuronConnection<DataType> *>(nodeConnection);
  //    DataType desiredWeight =
  //        desiredConnectionSum -
  //        (mConnectionOutputSum - neuronConnection->output());
  //    DataType weightError = neuronConnection->weight() - desiredWeight;
  //    neuronConnection->setWeight(kLearningRate * (weightError) /
  //                                mInputNodeConnections.size());
  //  }

  mActivation.reset();
}

} // namespace NodeNetwork
} // namespace Core

#endif // Neuron_H
