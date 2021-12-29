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

/* Weight vs. Bias
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

/* Backward propagation
 * \link https://www.youtube.com/watch?v=lWzdntI0WBo

   An improved weight "W'" for the current weight "W" is given by:
       W' = W - r * dC/dW
   where "r" is the "learning rate" and dC/dW is the change in "cost" relative
   to a change in "weight".

   using the chain rule of differentiation we can rewrite this as:
       W' = W - r * dC/dA * dA/dW
   where "A" is the activation value.
*/

/* Backward propagation example 1
   for 2 nodes connected as follows:

   I  W   A
   0----->0

   where "I" is the input value, "W" is the connecton weight and "A" is the
   activation function;

   given:
   - a cost function: C = (A - P)^2 where "A" is the current activation value
   and "P" is the desired activation value,
   - and sigmoid as the activation function: A = 1 / (1 - e^(-I*W))

   dC/dA = 2 * (A - P)
   the derivative of the cost function relative to the activation value.

   dA/dW = I * A * (1 - A)
   the derivative of the sigmoid function relative to "W" where "A" is the
   result of the sigmoid function.

   W' = W - r * 2 * (A - P) * I * A * (1 - A)
   W' = W - 2 * I * r * (A^2 - A^3 - A*p - (A^2)*P)
*/

/* Backward propagation example 2
   for 1 input node connected to 2 outputs instead of 1;

   the equation:
   W' = W - r * dC/dA * dA/dW
   becomes:
   W' = W - r * sum(dC/dA * dA/dW)

   where for each derivative in the summation, we substitute the values for each
   output's activation value and desired activation value.
*/

/* Backward propagation example 3
   for 2 nodes connected and a bias term "B" as follows:

   I1  W1_1
   0------.      A1
          |---.--0
   0------'   |
   I2  W1_2   |
              |
              |
   B----------'

   the updated weight is given by:
   W1_j' = W1_j - r * dC/dA * dA/dW * Ij
   where j is replaced by the weight number we are working with.

   the updated bias is given by:
   B' = B - r * dC/dA * dA/dB
   where j is replaced by the weight number we are working with.
*/

/* Backward propagation example 4
   for 2 nodes connected to the first input node of the previous example.


   X1  W0_1
   0----.       A0  W2_1
        |-------0------.      A2
   0----'              |---.--0
   X2  W0_2     0------'   |
                A1  W2_2   |
                           |
                           |
                B----------'

   the updated weight is given by:
   W0_j' = W0_j - r * dC/dA0 * dA0/dW2_1 * dW2_1/dW0_j * W2_1 * Xj
   where j is replaced by the weight number we are working with.

   note that the first 2 derivates are the sames as calculated in example 3.
*/

/* Backward propagation generalization
 * \link https://www.youtube.com/watch?v=lWzdntI0WBo

   let dC/dA = (A - P)
   let dA/dW = g'(A)

   for output neurons:
   Wk_j' = Wk_j - r * (Ak - Pk) * g'(Ak) * Aj

   for the kth output neuron, and the jth weight going to that neuron.

   for hidden neurons:
   Wj_i' = Wj_i - r * sum{(Ak - Pk) * g'(Ak) * Wk_j} * g'(Aj) * Xi

   NOTE:
   the sum over 'k' output neurons only sums the outputs which are
   connected to the current hidden neuron.
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

template <typename DataType> DataType reLu(const DataType input) {
  return std::max(DataType(0), input);
}
//----------------------------------------------------------------------------

// ___ACTIVATION FUNCTION DERIVATIVES dA/dw___
//----------------------------------------------------------------------------
template <typename DataType> DataType sigmoidDerivative(const DataType input) {
  DataType sigmoidResult = sigmoid(input);
  return input * sigmoidResult * (DataType(1) - sigmoidResult);
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
double kLearningRate = 0.01;
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
        mBias(0 /*kNormalDist<DataType>(randomizer)*/),
        mActivationFunction(sigmoid), mActivation(std::nullopt) {}

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
  connectionOutputSum /= mInputNodeConnections.size();

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
