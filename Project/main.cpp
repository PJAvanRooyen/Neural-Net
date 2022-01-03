#include "Core/ModuleManager/ModuleManager.h"
#include "UI/Application/Application.h"

// test
#include "Core/NeuralNetwork/Neuron.h"
#include <bitset>
#include <iostream>

static constexpr int inputLayerSize = 2;
static constexpr int outputLayerSize = 2;
// test

#include <QApplication>
#include <QWidget>

struct Print {
  static void
  printWeights(std::vector<std::vector<
                   std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
                   &layerConnections) {
    std::cout << "weights: ";
    for (auto &layer : layerConnections) {
      std::cout << "{";
      for (auto &node : layer) {
        std::cout << "[";
        for (auto connection : node) {
          std::cout << "(" << connection->weight() << "),";
        }
        std::cout << "],";
      }
      std::cout << "},";
    }
    std::cout << "\n";
  };

  static void
  printBiases(std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
                  &layerNeurons) {
    std::cout << "biases: ";
    for (auto &layer : layerNeurons) {
      std::cout << "{";
      for (auto &node : layer) {
        std::cout << "[" << node->bias() << "],";
      }
      std::cout << "},";
    }
    std::cout << "\n";
  };

  static void printSensitivities(
      std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
          &layerNeurons) {
    std::cout << "sensitivities: ";
    for (auto &layer : layerNeurons) {
      std::cout << "{";
      for (auto &node : layer) {
        std::cout << "[" << node->sensitivity() << "],";
      }
      std::cout << "},";
    }
    std::cout << "\n";
  };

  static double
  printErrors(std::vector<Core::NodeNetwork::Neuron<double> *> &outputNodes,
              std::bitset<outputLayerSize> desiredValues) {
    double mse = 0;

    std::cout << "error: ";
    for (unsigned long neuronIdx = 0; neuronIdx < outputNodes.size();
         ++neuronIdx) {
      double error = desiredValues[neuronIdx] - outputNodes[neuronIdx]->value();
      mse += std::pow(error, 2);
      std::cout << "(" << error << "),";
    }
    mse /= outputLayerSize;
    std::cout << " MSE = " << mse;
    std::cout << "\n";
    return mse;
  };

  static void
  printActivations(std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
                       layerNeurons) {
    std::cout << "activations: ";
    for (auto &layer : layerNeurons) {
      std::cout << "{";
      for (auto &node : layer) {
        std::cout << "[" << node->value() << "],";
      }
      std::cout << "},";
    }
    std::cout << "\n";
  };

  static void printWeightUpdate(
      std::vector<std::vector<std::vector<double>>> prevWeights,
      std::vector<std::vector<
          std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
          layerConnections) {
    std::cout << "equations: ";
    for (unsigned long long layerIdx = 0; layerIdx < layerConnections.size();
         ++layerIdx) {
      auto &layer = layerConnections[layerIdx];

      std::cout << "{";
      for (unsigned long long nodeIdx = 0; nodeIdx < layer.size(); ++nodeIdx) {
        auto &node = layer[nodeIdx];

        std::cout << "[";
        for (unsigned long long connectionIdx = 0; connectionIdx < node.size();
             ++connectionIdx) {
          auto &connection = node[connectionIdx];

          std::cout << "(" << connection->weight() << " = "
                    << prevWeights[layerIdx][nodeIdx][connectionIdx] << " + "
                    << Core::NodeNetwork::kLearningRate << "*"
                    << static_cast<Core::NodeNetwork::Neuron<double> *>(
                           connection->destinationNode())
                           ->sensitivity()
                    << "*"
                    << static_cast<Core::NodeNetwork::Neuron<double> *>(
                           connection->sourceNode())
                           ->value()
                    << "),";
        }
        std::cout << "],";
      }
      std::cout << "},";
    }
    std::cout << "\n";
  };

  static std::vector<std::vector<std::vector<double>>>
  getWeights(std::vector<std::vector<
                 std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
                 layerConnections) {
    std::vector<std::vector<std::vector<double>>> weights;
    weights.resize(layerConnections.size());

    for (unsigned long long layerIdx = 0; layerIdx < layerConnections.size();
         ++layerIdx) {
      auto &layer = layerConnections[layerIdx];
      weights[layerIdx].resize(layerConnections[layerIdx].size());

      for (unsigned long long nodeIdx = 0; nodeIdx < layer.size(); ++nodeIdx) {
        auto &node = layer[nodeIdx];
        weights[layerIdx][nodeIdx].resize(
            layerConnections[layerIdx][nodeIdx].size());

        for (unsigned long long connectionIdx = 0; connectionIdx < node.size();
             ++connectionIdx) {
          auto &connection = node[connectionIdx];

          weights[layerIdx][nodeIdx][connectionIdx] = connection->weight();
        }
      }
    }
    return weights;
  };
};

struct Test {
  static constexpr unsigned long long kLearningIterations = 1000000;
  static constexpr unsigned long long kLearnPoll = kLearningIterations / 100;

  // desired network outputs
  static std::bitset<inputLayerSize>
  desiredOutputs(std::bitset<inputLayerSize> inputs) {
    std::bitset<outputLayerSize> outputs{0};

    outputs.set(0, inputs[0] && !inputs[1]);
    outputs.set(1, !inputs[0] && inputs[1]);

    return outputs;
  };

  static bool
  test(std::bitset<inputLayerSize> inputValues,
       std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
           &layerNeurons,
       std::vector<std::vector<
           std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
           &layerConnections,
       const bool learn, const bool debug) {

    std::vector<Core::NodeNetwork::Neuron<double> *> &inputLayer =
        layerNeurons.front();
    std::vector<Core::NodeNetwork::Neuron<double> *> &outputLayer =
        layerNeurons.back();

    // set test values
    for (unsigned long neuronIdx = 0; neuronIdx < inputLayer.size();
         ++neuronIdx) {
      inputLayer[neuronIdx]->setValue(inputValues[neuronIdx]);
    }

    // activate
    for (auto *neuron : outputLayer) {
      neuron->activate();
    }

    auto desired = desiredOutputs(inputValues);

    // show debug info
    if (debug) {
      std::cout << "pre-update:\n";
      Print::printWeights(layerConnections);
      Print::printBiases(layerNeurons);
      Print::printActivations(layerNeurons);
      Print::printSensitivities(layerNeurons);
      Print::printErrors(outputLayer, desired);
    }

    // compare to desired outputs
    std::bitset<outputLayerSize> obtained;
    for (unsigned long neuronIdx = 0; neuronIdx < outputLayer.size();
         ++neuronIdx) {
      bool obtainedValue = std::round(outputLayer[neuronIdx]->value());
      obtained.set(neuronIdx, obtainedValue);
    }

    // teach the network
    if (learn) {
      auto desired = desiredOutputs(inputValues);
      // set the desiredOutput of the output neurons
      for (unsigned long neuronIdx = 0; neuronIdx < outputLayer.size();
           ++neuronIdx) {
        bool desiredValue = desired[neuronIdx];
        outputLayer[neuronIdx]->setDesiredActivation(desiredValue);
      }

      for (auto *neuron : inputLayer) {
        neuron->backPropagate();
      }
    }

    // deactivate (to get ready for new inputs)
    for (auto *neuron : outputLayer) {
      neuron->deActivate();
    }

    if (learn && debug) {
      // set test values
      for (unsigned long neuronIdx = 0; neuronIdx < inputLayer.size();
           ++neuronIdx) {
        inputLayer[neuronIdx]->setValue(inputValues[neuronIdx]);
      }

      // activate
      for (auto *neuron : outputLayer) {
        neuron->activate();
      }

      auto desired = desiredOutputs(inputValues);

      // show debug info
      if (debug) {
        std::cout << "post-update:\n";
        Print::printWeights(layerConnections);
        Print::printBiases(layerNeurons);
        Print::printActivations(layerNeurons);
        Print::printSensitivities(layerNeurons);
        Print::printErrors(outputLayer, desired);
      }

      // deactivate (to get ready for new inputs)
      for (auto *neuron : outputLayer) {
        neuron->deActivate();
      }
    }

    if (debug) {
      std::cout << "\n";
    }

    return desired == obtained;
  }

  static double
  testSet(std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
              &layerNeurons,
          std::vector<std::vector<
              std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
              &layerConnections,
          const bool learn, const bool debug) {

    std::vector<Core::NodeNetwork::Neuron<double> *> &inputLayer =
        layerNeurons.front();

    unsigned long long kTestingIterations = std::pow(2, inputLayer.size());
    unsigned long long correctCount = 0;

    for (unsigned long long i = 0; i < kTestingIterations; ++i) {

      std::bitset<inputLayerSize> inputValues{i};

      // run test
      bool correct =
          test(inputValues, layerNeurons, layerConnections, learn, debug);
      if (correct) {
        ++correctCount;
      }
    }

    double accuracy = 100.0 * correctCount / kTestingIterations;
    if (debug) {
      std::cout << "===========================\n";
      std::cout << "accuracy of test set: " << accuracy << "\n";
      std::cout << "===========================\n\n";
    }
    return accuracy;
  }

  static void learnFromInputSets(
      std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
          &layerNeurons,
      std::vector<std::vector<
          std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
          &layerConnections,
      const bool debug) {
    std::vector<double> accuracies;

    for (unsigned long long i = 0; i < kLearningIterations; ++i) {
      if (i % kLearnPoll == 0) {
        // test the current weights without updating the network.
        double accuracy = testSet(layerNeurons, layerConnections, true, true);
        accuracies.push_back(accuracy);
      } else {
        // teach the network
        double accuracy = testSet(layerNeurons, layerConnections, true, false);
        Q_UNUSED(accuracy)
        // accuracies.push_back(accuracy);
      }
    }

    if (debug) {
      std::cout << "accuracies: ";
      for (auto accuracy : accuracies) {
        std::cout << accuracy << ", ";
      }
      std::cout << "\n\n";
    }
  }

  static void learnFromRandomInputs(
      std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>>
          &layerNeurons,
      std::vector<std::vector<
          std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
          &layerConnections,
      const bool debug) {
    unsigned long long correctCount = 0;
    std::vector<double> accuracies;

    std::bitset<inputLayerSize> inputs = {0};
    for (unsigned long long i = 0; i < kLearningIterations * 4; ++i) {
      for (unsigned long long nodeIdx = 0; nodeIdx < inputs.size(); ++nodeIdx) {
        inputs.set(nodeIdx, rand() % 2);
      }

      if (i != 0 && i % kLearnPoll == 0) {
        // test the current weights without updating the network.
        bool correct = test(inputs, layerNeurons, layerConnections, true, true);
        if (correct) {
          ++correctCount;
        }
        double accuracy = 100.0 * correctCount / kLearnPoll;
        accuracies.push_back(accuracy);
        correctCount = 0;
      } else {
        // teach the network
        bool correct =
            test(inputs, layerNeurons, layerConnections, true, false);
        if (correct) {
          ++correctCount;
        }
      }
    }

    if (debug) {
      std::cout << "accuracies: ";
      for (auto accuracy : accuracies) {
        std::cout << accuracy << ", ";
      }
      std::cout << "\n\n";
    }
  }
};

int main(int argc, char *argv[]) {
  std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  std::mt19937 engine; // Mersenne twister MT19937

  // input randomization seed
  srand(2);

  // start test
  Core::NodeNetwork::Neuron<double> *l1n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l1n2 =
      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l1n3 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l1n4 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l1n5 =
  //      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::Neuron<double> *l2n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l2n2 =
      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l2n3 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l2n4 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l2n5 =
  //      new Core::NodeNetwork::Neuron<double>();

  Core::NodeNetwork::Neuron<double> *l3n1 =
      new Core::NodeNetwork::Neuron<double>();
  Core::NodeNetwork::Neuron<double> *l3n2 =
      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l3n3 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l3n4 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l3n5 =
  //      new Core::NodeNetwork::Neuron<double>();

  //  Core::NodeNetwork::Neuron<double> *l4n1 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l4n2 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l4n3 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l4n4 =
  //      new Core::NodeNetwork::Neuron<double>();
  //  Core::NodeNetwork::Neuron<double> *l4n5 =
  //      new Core::NodeNetwork::Neuron<double>();

  // l1 -> l2
  //---------------------------------------------------------
  Core::NodeNetwork::NeuronConnection c_l1n1_l2n1 =
      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n1);
  Core::NodeNetwork::NeuronConnection c_l1n2_l2n1 =
      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n1);
  //  Core::NodeNetwork::NeuronConnection c_l1n3_l2n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n3, l2n1);
  //  Core::NodeNetwork::NeuronConnection c_l1n4_l2n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n4, l2n1);
  //  Core::NodeNetwork::NeuronConnection c_l1n5_l2n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n5, l2n1);

  Core::NodeNetwork::NeuronConnection c_l1n1_l2n2 =
      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n2);
  Core::NodeNetwork::NeuronConnection c_l1n2_l2n2 =
      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n2);
  //  Core::NodeNetwork::NeuronConnection c_l1n3_l2n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n3, l2n2);
  //  Core::NodeNetwork::NeuronConnection c_l1n4_l2n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n4, l2n2);
  //  Core::NodeNetwork::NeuronConnection c_l1n5_l2n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n5, l2n2);

  //  Core::NodeNetwork::NeuronConnection c_l1n1_l2n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n3);
  //  Core::NodeNetwork::NeuronConnection c_l1n2_l2n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n3);
  //  Core::NodeNetwork::NeuronConnection c_l1n3_l2n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n3, l2n3);
  //  Core::NodeNetwork::NeuronConnection c_l1n4_l2n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n4, l2n3);
  //  Core::NodeNetwork::NeuronConnection c_l1n5_l2n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n5, l2n3);

  //  Core::NodeNetwork::NeuronConnection c_l1n1_l2n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n4);
  //  Core::NodeNetwork::NeuronConnection c_l1n2_l2n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n4);
  //  Core::NodeNetwork::NeuronConnection c_l1n3_l2n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n3, l2n4);
  //  Core::NodeNetwork::NeuronConnection c_l1n4_l2n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n4, l2n4);
  //  Core::NodeNetwork::NeuronConnection c_l1n5_l2n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n5, l2n4);

  //  Core::NodeNetwork::NeuronConnection c_l1n1_l2n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n1, l2n5);
  //  Core::NodeNetwork::NeuronConnection c_l1n2_l2n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n2, l2n5);
  //  Core::NodeNetwork::NeuronConnection c_l1n3_l2n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n3, l2n5);
  //  Core::NodeNetwork::NeuronConnection c_l1n4_l2n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n4, l2n5);
  //  Core::NodeNetwork::NeuronConnection c_l1n5_l2n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l1n5, l2n5);
  //---------------------------------------------------------

  // l2 -> l3
  //---------------------------------------------------------
  Core::NodeNetwork::NeuronConnection c_l2n1_l3n1 =
      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n1);
  Core::NodeNetwork::NeuronConnection c_l2n2_l3n1 =
      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n1);
  //  Core::NodeNetwork::NeuronConnection c_l2n3_l3n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n1);
  //  Core::NodeNetwork::NeuronConnection c_l2n4_l3n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n4, l3n1);
  //  Core::NodeNetwork::NeuronConnection c_l2n5_l3n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n5, l3n1);

  Core::NodeNetwork::NeuronConnection c_l2n1_l3n2 =
      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n2);
  Core::NodeNetwork::NeuronConnection c_l2n2_l3n2 =
      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n2);
  //  Core::NodeNetwork::NeuronConnection c_l2n3_l3n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n2);
  //  Core::NodeNetwork::NeuronConnection c_l2n4_l3n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n4, l3n2);
  //  Core::NodeNetwork::NeuronConnection c_l2n5_l3n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n5, l3n2);

  //  Core::NodeNetwork::NeuronConnection c_l2n1_l3n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n3);
  //  Core::NodeNetwork::NeuronConnection c_l2n2_l3n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n3);
  //  Core::NodeNetwork::NeuronConnection c_l2n3_l3n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n3);
  //  Core::NodeNetwork::NeuronConnection c_l2n4_l3n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n4, l3n3);
  //  Core::NodeNetwork::NeuronConnection c_l2n5_l3n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n5, l3n3);

  //  Core::NodeNetwork::NeuronConnection c_l2n1_l3n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n4);
  //  Core::NodeNetwork::NeuronConnection c_l2n2_l3n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n4);
  //  Core::NodeNetwork::NeuronConnection c_l2n3_l3n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n4);
  //  Core::NodeNetwork::NeuronConnection c_l2n4_l3n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n4, l3n4);
  //  Core::NodeNetwork::NeuronConnection c_l2n5_l3n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n5, l3n4);

  //  Core::NodeNetwork::NeuronConnection c_l2n1_l3n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n1, l3n5);
  //  Core::NodeNetwork::NeuronConnection c_l2n2_l3n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n2, l3n5);
  //  Core::NodeNetwork::NeuronConnection c_l2n3_l3n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n3, l3n5);
  //  Core::NodeNetwork::NeuronConnection c_l2n4_l3n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n4, l3n5);
  //  Core::NodeNetwork::NeuronConnection c_l2n5_l3n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l2n5, l3n5);
  //---------------------------------------------------------

  // l3 -> l4
  //---------------------------------------------------------
  //  Core::NodeNetwork::NeuronConnection c_l3n1_l4n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n1, l4n1);
  //  Core::NodeNetwork::NeuronConnection c_l3n2_l4n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n2, l4n1);
  //  Core::NodeNetwork::NeuronConnection c_l3n3_l4n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n3, l4n1);
  //  Core::NodeNetwork::NeuronConnection c_l3n4_l4n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n4, l4n1);
  //  Core::NodeNetwork::NeuronConnection c_l3n5_l4n1 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n5, l4n1);

  //  Core::NodeNetwork::NeuronConnection c_l3n1_l4n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n1, l4n2);
  //  Core::NodeNetwork::NeuronConnection c_l3n2_l4n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n2, l4n2);
  //  Core::NodeNetwork::NeuronConnection c_l3n3_l4n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n3, l4n2);
  //  Core::NodeNetwork::NeuronConnection c_l3n4_l4n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n4, l4n2);
  //  Core::NodeNetwork::NeuronConnection c_l3n5_l4n2 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n5, l4n2);

  //  Core::NodeNetwork::NeuronConnection c_l3n1_l4n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n1, l4n3);
  //  Core::NodeNetwork::NeuronConnection c_l3n2_l4n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n2, l4n3);
  //  Core::NodeNetwork::NeuronConnection c_l3n3_l4n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n3, l4n3);
  //  Core::NodeNetwork::NeuronConnection c_l3n4_l4n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n4, l4n3);
  //  Core::NodeNetwork::NeuronConnection c_l3n5_l4n3 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n5, l4n3);

  //  Core::NodeNetwork::NeuronConnection c_l3n1_l4n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n1, l4n4);
  //  Core::NodeNetwork::NeuronConnection c_l3n2_l4n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n2, l4n4);
  //  Core::NodeNetwork::NeuronConnection c_l3n3_l4n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n3, l4n4);
  //  Core::NodeNetwork::NeuronConnection c_l3n4_l4n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n4, l4n4);
  //  Core::NodeNetwork::NeuronConnection c_l3n5_l4n4 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n5, l4n4);

  //  Core::NodeNetwork::NeuronConnection c_l3n1_l4n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n1, l4n5);
  //  Core::NodeNetwork::NeuronConnection c_l3n2_l4n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n2, l4n5);
  //  Core::NodeNetwork::NeuronConnection c_l3n3_l4n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n3, l4n5);
  //  Core::NodeNetwork::NeuronConnection c_l3n4_l4n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n4, l4n5);
  //  Core::NodeNetwork::NeuronConnection c_l3n5_l4n5 =
  //      Core::NodeNetwork::NeuronConnection<double>(l3n5, l4n5);
  //---------------------------------------------------------

  std::vector<Core::NodeNetwork::Neuron<double> *> inputLayer = {
      l1n1, l1n2 /*, l1n3, l1n4, l1n5*/};
  std::vector<Core::NodeNetwork::Neuron<double> *> outputLayer = {
      l3n1, l3n2 /*l4n1, l4n2, l4n3, l4n4, l4n5*/};

  std::vector<std::vector<Core::NodeNetwork::Neuron<double> *>> layerNeurons = {
      inputLayer, {l2n1, l2n2}, outputLayer};

  std::vector<
      std::vector<std::vector<Core::NodeNetwork::NeuronConnection<double> *>>>
      layerConnections = {
          {{&c_l1n1_l2n1, &c_l1n1_l2n2}, {&c_l1n2_l2n1, &c_l1n2_l2n2}},
          {{&c_l2n1_l3n1, &c_l2n1_l3n2}, {&c_l2n2_l3n1, &c_l2n2_l3n2}}};

  // teach the network
  Test::learnFromRandomInputs(layerNeurons, layerConnections, true);

  // UI
  //=========================================================================
  QApplication a(argc, argv);
  UI::Application::Application application = UI::Application::Application();

  application.view()->show();

  return a.exec();
}
