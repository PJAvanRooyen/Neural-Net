#ifndef Neuron_H
#define Neuron_H

#include "Core/NodeNetwork/Node.h"
#include "Core/NodeNetwork/NodeConnection.h"
#include "Shared/NeuralNetwork/Defines.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include <optional>
#include <qlogging.h>
#include <random>

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

namespace Core {
namespace NodeNetwork {

template <typename DataType> class NeuronConnection;

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
  return sigmoidResult * (DataType(1) - sigmoidResult);
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
//----------------------------------------------------------------------------
static double sLearningRate;

template <typename DataType>
std::normal_distribution<DataType>
    sNormalDist = std::normal_distribution<DataType>(DataType(0), DataType(1));

static std::default_random_engine sRandomizer;

template <typename DataType> class Neuron : public Node {

  typedef DataType (*ActivationFunction)(const DataType);

  typedef DataType (*BiasFunction)(const DataType, const DataType);

  typedef DataType (*ActivationFunctionDerivative)(const DataType);

  typedef DataType (*CostFunctionDerivative)(const DataType, const DataType);

public:
  Neuron()
      : Node(), mBiasFunction(constantOffset), mActivationFunction(sigmoid),
        mActivationFunctionDerivative(sigmoidDerivative),
        mCostFunctionDerivative(meanSquareErrorDerivative),
        mData({std::nullopt, std::nullopt, std::nullopt, std::nullopt}) {}

  ~Neuron();

  void init() {
    if (!mInputNodeConnections.empty() && !mOutputNodeConnections.empty()) {
      mData.bias.emplace(sNormalDist<DataType>(sRandomizer));
    }
  }

  const std::vector<NeuronConnection<DataType> *> &
  outputNeuronConnections() const {
    return reinterpret_cast<const std::vector<NeuronConnection<DataType> *> &>(
        mOutputNodeConnections);
  }

  DataType value() {
    if (mData.activation.has_value()) {
      return mData.activation.value();
    }
    return activate();
  }

  void setValue(const DataType value) { mData.activation.emplace(value); }

  DataType bias() const {
    if (mData.bias.has_value()) {
      return mData.bias.value();
    }
    return DataType(1.0);
  }

  void updateBias() {
    // input and output nodes should not be biased.
    if (mInputNodeConnections.empty() || mOutputNodeConnections.empty()) {
      return;
    }

    Q_ASSERT(mData.sensitivity.has_value());
    Q_ASSERT(mData.bias.has_value());
    mData.bias.emplace(mData.bias.value() +
                       sLearningRate * mData.sensitivity.value());
  }

  DataType activate();

  void setDesiredActivation(const DataType desiredActivation) {
    mData.desiredActivation.emplace(desiredActivation);
  }

  void backPropagate();

  DataType sensitivity();

  void deActivate();

  const Shared::NodeNetwork::NeuronData<DataType> &data() const {
    return mData;
  }

private:
  /*
   * \brief function pointer for the bias function.
   */
  BiasFunction mBiasFunction;

  /*
   * \brief function pointer for the activation function.
   */
  ActivationFunction mActivationFunction;

  ActivationFunctionDerivative mActivationFunctionDerivative;

  CostFunctionDerivative mCostFunctionDerivative;

  Shared::NodeNetwork::NeuronData<DataType> mData;

}; // namespace NodeNetwork

template <typename DataType> class NeuronConnection : public NodeConnection {

  typedef DataType (*WeightFunction)(DataType, DataType);

public:
  NeuronConnection(Neuron<DataType> *sourceNeuron, Neuron<DataType> *destNeuron)
      : NodeConnection(sourceNeuron, destNeuron), mWeightFunction(LinearScale),
        mData({sNormalDist<DataType>(sRandomizer), std::nullopt}) {}

  DataType weight() const { return mData.weight; }

  void setWeight(const DataType weight) { mData.weight = weight; }

  DataType value() {
    if (mData.activation.has_value()) {
      return mData.activation.value();
    }
    return activate();
  }

  DataType activate() {
    Neuron<DataType> *sourceNeuron = static_cast<Neuron<DataType> *>(mSource);
    const DataType sourceActivation = sourceNeuron->activate();
    const DataType activation = mWeightFunction(sourceActivation, mData.weight);

    mData.activation.emplace(activation);
    return mData.activation.value();
  }

  void updateWeight() {
    Neuron<DataType> *sourceNeuron = static_cast<Neuron<DataType> *>(mSource);
    Neuron<DataType> *destinationNeuron =
        static_cast<Neuron<DataType> *>(mDestination);

    mData.weight += sLearningRate * destinationNeuron->sensitivity() *
                    sourceNeuron->value();
  }

  DataType backPropagate() const {
    Neuron<DataType> *destinationNeuron =
        static_cast<Neuron<DataType> *>(mDestination);

    destinationNeuron->backPropagate();

    return mData.weight * destinationNeuron->sensitivity();
  }

  void deActivate() {
    // Note: each connection can only be entered/activated once per run, so no
    // need to un-set their activation values. Calling activate should always
    // recaclulate the activation value.

    Neuron<DataType> *sourceNeuron = static_cast<Neuron<DataType> *>(mSource);

    sourceNeuron->deActivate();
  }

  const Shared::NodeNetwork::NeuronConnectionData<DataType> &data() const {
    return mData;
  }

private:
  /*
   * \brief function pointer for the weight function.
   */
  WeightFunction mWeightFunction;

  Shared::NodeNetwork::NeuronConnectionData<DataType> mData;
};

template <typename DataType> inline DataType Neuron<DataType>::activate() {

  if (mData.activation.has_value()) {
    return mData.activation.value();
  } else if (mInputNodeConnections.size() == 0) {
    // error, activations of input neurons should already have been set
    // manually.
    Q_ASSERT(false);
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

  DataType biasedSum = connectionOutputSum;
  // pass the sum through this neuron's bias function.
  if (mData.bias.has_value()) {
    biasedSum = mBiasFunction(connectionOutputSum, mData.bias.value());
  }

  // pass the sum through this neuron's activation function.
  mData.activation.emplace(mActivationFunction(biasedSum));

  return mData.activation.value();
}

template <typename DataType> inline void Neuron<DataType>::backPropagate() {
  // if the sensitivity has already been calculated, then all branches after
  // this neuron have already been updated.
  if (mData.sensitivity.has_value()) {
    return;
  }

  // if it is an input neuron, it does not have any sensitivity, just continue
  // to back propagate.
  if (mInputNodeConnections.size() == 0) {
    for (auto nodeConnection : mOutputNodeConnections) {
      NeuronConnection<DataType> *neuronConnection =
          static_cast<NeuronConnection<DataType> *>(nodeConnection);
      neuronConnection->backPropagate();
    }

    return;
  }

  // calculate the neuron's sensitivity.
  sensitivity();

  // update this neuron's bias
  updateBias();

  // for each input connection, update the connection's weight.
  for (auto nodeConnection : mInputNodeConnections) {
    NeuronConnection<DataType> *neuronConnection =
        static_cast<NeuronConnection<DataType> *>(nodeConnection);

    neuronConnection->updateWeight();
  }
}

template <typename DataType> inline DataType Neuron<DataType>::sensitivity() {
  if (mData.sensitivity.has_value()) {
    return mData.sensitivity.value();
  }

  if (!mData.activation.has_value()) {
    // error
    Q_ASSERT(false);
    return DataType(0);
  }

  // get the activation value, it must already exist for back propagation to
  // work.
  DataType activation = mData.activation.value();

  DataType dA_da = mActivationFunctionDerivative(activation);

  if (mOutputNodeConnections.size() == 0) {
    //   for output neurons:
    //   Wk_j' = Wk_j + r * (Pk - Ak) * g'(Ak) * Aj

    if (!mData.desiredActivation.has_value()) {
      // error can't back propagate without desired output.
      Q_ASSERT(false);
      return DataType(0);
    }

    // output's sensitivity replaces the activation value with the cost
    // derivative.
    DataType dC_dA =
        mCostFunctionDerivative(activation, mData.desiredActivation.value());
    mData.sensitivity.emplace(dC_dA * dA_da);
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
    mData.sensitivity.emplace(sensitivity);
  }

  return mData.sensitivity.value();
}

template <typename DataType> inline void Neuron<DataType>::deActivate() {
  if (!mData.activation.has_value() && !mData.sensitivity.has_value()) {
    return;
  }

  for (auto nodeConnection : mInputNodeConnections) {
    NeuronConnection<DataType> *neuronConnection =
        static_cast<NeuronConnection<DataType> *>(nodeConnection);

    neuronConnection->deActivate();
  }

  mData.activation.reset();
  mData.sensitivity.reset();
}

} // namespace NodeNetwork
} // namespace Core

#endif // Neuron_H
