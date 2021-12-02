#ifndef NodeConnection_H
#define NodeConnection_H

namespace Core {
namespace NodeNetwork {

class NodeConnection {
public:
  NodeConnection();

  ~NodeConnection();
};

template <typename DataType> class NeuronConnection : public NodeConnection {
  typedef DataType (*BiasFunction)(DataType);

public:
  NeuronConnection(const BiasFunction &biasFunction,
                   const DataType initialBias = 1)
      : NodeConnection(), mBiasFunction(biasFunction), mBias(initialBias) {}

  ~NeuronConnection();

  DataType activate(const DataType input) const {
    return mBiasFunction(input, mBias);
  }

private:
  /*
   * \brief function pointer for the bias function.
   */
  BiasFunction mBiasFunction;

  DataType mBias;
};

template <typename DataType>
DataType biasFunctionConstant(const DataType input, const DataType bias) {
  return input + bias;
}

} // namespace NodeNetwork
} // namespace Core

#endif // NodeConnection_H
