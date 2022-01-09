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
   - a cost function: C = (P - A)^2/2 where "A" is the current activation value
   and "P" is the desired activation value,
   - and sigmoid as the activation function: A = 1 / (1 - e^(-I*W))

   dC/dA = (P - A)
   the derivative of the cost function relative to the activation value.

   dA/dW = A * (1 - A)
   the derivative of the sigmoid function relative to "W" where "A" is the
   result of the sigmoid function with the current activation value as input.
*/

/* Backward propagation example 2
   for 1 input node connected to 2 outputs instead of 1;

   the equation:
   W' = W - r * dC/dA * dA/dW
   becomes:
   W' = W - r * sum(dC/dA * dA/dW * W)

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
   W1_j' = W1_j + r * dC/dA * dA/dW * Ij
   where j is replaced by the weight number we are working with.

   the updated bias is given by:
   B' = B + r * dC/dA * dA/dB
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
   W0_j' = W0_j + r * dC/dA0 * dA0/dW2_1 * dW2_1/dW0_j * W2_1 * Xj
   where j is replaced by the weight number we are working with.

   note that the first 2 derivates are the sames as calculated in example 3.
*/

/* Backward propagation generalization
 * \link https://www.youtube.com/watch?v=lWzdntI0WBo

   let dC/dA = (P - A)
   let dA/dW = g'(A)

   for output neurons:
   Wk_j' = Wk_j + r * (Pk - Ak) * g'(Ak) * Aj

   for the kth output neuron, and the jth weight going to that neuron.

   for hidden neurons:
   Wj_i' = Wj_i + r * g'(Aj) * Ai * sum{(Pk - Ak) * g'(Ak) * Wk_j}

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

// ___ACTIVATION FUNCTION DERIVATIVES dA/da___
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
DataType meanSquareError(const DataType output, const DataType desiredOutput) {
  return std::pow(desiredOutput - output, 2) / 2;
}

// ___COST FUNCTION DERIVATIVE dC/dA___
// where C is the cost, and A is the activation value
template <typename DataType>
DataType meanSquareErrorDerivative(const DataType output,
                                   const DataType desiredOutput) {
  return (desiredOutput - output);
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

  typedef DataType (*ActivationFunctionDerivative)(const DataType);

  typedef DataType (*CostFunctionDerivative)(const DataType, const DataType);

public:
  Neuron()
      : Node(), mBiasFunction(constantOffset),
        mBias(kNormalDist<DataType>(randomizer)), mActivationFunction(sigmoid),
        mActivation(std::nullopt),
        mActivationFunctionDerivative(sigmoidDerivative),
        mCostFunctionDerivative(meanSquareErrorDerivative),
        mSensitivity(std::nullopt), mDesiredActivation(std::nullopt) {}

  ~Neuron();

  DataType bias() const { return mBias; }

  DataType value() {
    if (mActivation.has_value()) {
      return mActivation.value();
    }
    return activate();
  }

  void setValue(const DataType value) { mActivation.emplace(value); }

  DataType activate();

  void setDesiredActivation(const DataType desiredActivation) {
    mDesiredActivation.emplace(desiredActivation);
  }

  DataType backPropagate();

  DataType sensitivity();

  void deActivate();

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

  ActivationFunctionDerivative mActivationFunctionDerivative;

  CostFunctionDerivative mCostFunctionDerivative;

  /*
   * \brief sensitivity = dC/dA * dA/dB for current activation value.
   */
  std::optional<DataType> mSensitivity;

  std::optional<DataType> mDesiredActivation;
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
    const DataType sourceActivation = sourceNeuron->activate();
    const DataType activation = mWeightFunction(sourceActivation, mWeight);

    mActivation.emplace(activation);
    return mActivation.value();
  }

  void updateWeight(const DataType destinationNodeSensitivity) {
    Neuron<DataType> *sourceNeuron = static_cast<Neuron<DataType> *>(mSource);

    mWeight +=
        kLearningRate * destinationNodeSensitivity * sourceNeuron->value();
  }

  DataType backPropagate() const {
    Neuron<DataType> *destinationNeuron =
        static_cast<Neuron<DataType> *>(mDestination);

    const DataType sensitivity = destinationNeuron->backPropagate();
    return mWeight * sensitivity;
  }

  void deActivate() {
    // Note: each connection can only be entered/activated once per run, so no
    // need to un-set their activation values. Calling activate should always
    // recaclulate the activation value.

    Neuron<DataType> *sourceNeuron = static_cast<Neuron<DataType> *>(mSource);

    sourceNeuron->deActivate();
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

  if (mActivation.has_value()) {
    return mActivation.value();
  } else if (mInputNodeConnections.size() == 0) {
    // error, activations of input neurons should already have been set
    // manually.
    return DataType(0);
  }

  // sum the output values of all input connections.
  auto connectionOutput =
      [](const DataType val,
         Shared::NodeNetwork::AbstractNodeConnection *nodeConnection) {
        auto *neuronConnection =
            static_cast<NeuronConnection<DataType> *>(nodeConnection);
        return val + neuronConnection->activate();
      };

  DataType connectionOutputSum = std::accumulate(mInputNodeConnections.cbegin(),
                                                 mInputNodeConnections.cend(),
                                                 DataType(0), connectionOutput);
  // normalize the value
  // connectionOutputSum /= std::sqrt(mInputNodeConnections.size());

  // pass the sum through this neuron's bias function.
  const DataType biasedSum = mBiasFunction(connectionOutputSum, mBias);

  // pass the sum through this neuron's activation function.
  mActivation.emplace(mActivationFunction(biasedSum));

  return mActivation.value();
}

template <typename DataType> inline DataType Neuron<DataType>::backPropagate() {
  if (!mActivation.has_value()) {
    // error, must have activated for it to back propagate.
    return DataType(0);
  }

  if (mSensitivity.has_value()) {
    // don't re-update bias or re-calculate sensitivity if it has already been
    // calculated.
    return mSensitivity.value();
  }

  // calculate the sensitivity if not yet calculated.
  DataType sensitivity = this->sensitivity();

  // update this neuron's bias
  mBias += kLearningRate * sensitivity;

  // for each input connection, update the connection's weight
  for (auto nodeConnection : mInputNodeConnections) {
    NeuronConnection<DataType> *neuronConnection =
        static_cast<NeuronConnection<DataType> *>(nodeConnection);

    neuronConnection->updateWeight(sensitivity);
  }
}

template <typename DataType> inline DataType Neuron<DataType>::sensitivity() {
  if (!mActivation.has_value()) {
    // error
    return DataType(0);
  }

  if (mSensitivity.has_value()) {
    return mSensitivity.value();
  }

  // get the activation value, it must already exist for back propagation to
  // work.
  DataType activation = mActivation.value();

  DataType dA_da = mActivationFunctionDerivative(activation);

  if (mOutputNodeConnections.size() == 0) {
    //   for output neurons:
    //   Wk_j' = Wk_j + r * (Pk - Ak) * g'(Ak) * Aj

    if (!mDesiredActivation.has_value()) {
      // error can't back propagate without desired output.
      return DataType(0);
    }

    // output's sensitivity replaces the activation value with the cost
    // derivative.
    DataType dC_dA =
        mCostFunctionDerivative(activation, mDesiredActivation.value());
    mSensitivity.emplace(dC_dA * dA_da);
  } else {
    //   for hidden neurons:
    //   Wj_i' = Wj_i + r * g'(Aj) * sum{ Wk_j * g'(Ak) * (Pk - Ak)}  * Ai

    DataType sensitivity = 0;
    for (auto nodeConnection : mOutputNodeConnections) {
      NeuronConnection<DataType> *neuronConnection =
          static_cast<NeuronConnection<DataType> *>(nodeConnection);

      sensitivity += neuronConnection->backPropagate();
    }
    sensitivity *= dA_da;
    mSensitivity.emplace(sensitivity);
  }

  return mSensitivity.value();
}

template <typename DataType> inline void Neuron<DataType>::deActivate() {
  if (!mActivation.has_value() && !mSensitivity.has_value()) {
    return;
  }

  for (auto nodeConnection : mInputNodeConnections) {
    NeuronConnection<DataType> *neuronConnection =
        static_cast<NeuronConnection<DataType> *>(nodeConnection);

    neuronConnection->deActivate();
  }

  mActivation.reset();
  mSensitivity.reset();
}

} // namespace NodeNetwork
} // namespace Core

#endif // Neuron_H
