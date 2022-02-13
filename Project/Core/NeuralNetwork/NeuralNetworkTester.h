#ifndef NeuralNetworkTester_H
#define NeuralNetworkTester_H

#include <optional>
#include <vector>

class QUuid;

namespace Core {
namespace NodeNetwork {

template <typename DataType> class NeuralNetwork;

class NeuralNetworkTester {
  static const unsigned char kPollCount;

public:
  static void irisTest(const std::optional<unsigned long> &dataSeed,
                       const unsigned long learningIterations,
                       const unsigned long testingIterations,
                       const QUuid &networkId,
                       Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                       const bool debug = true);

  static void
  test(const std::vector<std::pair<std::vector<double>, std::vector<double>>>
           learningSet,
       const std::vector<std::pair<std::vector<double>, std::vector<double>>>
           testingSet,
       const QUuid &networkId,
       Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
       const bool debug);

  static bool
  testIteration(const std::vector<double> &inputValues,
                const std::vector<double> &desiredOutputs,
                Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork,
                const bool learn);

}; // namespace NodeNetwork

} // namespace NodeNetwork
} // namespace Core

#endif // NeuralNetworkTester_H
