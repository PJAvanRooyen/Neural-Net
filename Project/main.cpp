#include "Core/ModuleManager/ModuleManager.h"
#include "UI/Application/Application.h"

// test
#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkLayer.h"
#include "Core/NeuralNetwork/Neuron.h"
#include "Shared/NodeNetwork/NodeNetworkFactory.h"
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
  desiredOutputs(const std::bitset<inputLayerSize> &inputs) {
    std::bitset<outputLayerSize> outputs{0};
    bool in0 = inputs[0];
    bool in1 = inputs[1];

    outputs.set(0, in0 && !in1);
    outputs.set(1, !in0 && in1);

    bool out0 = inputs[0];
    bool out1 = inputs[1];
    Q_UNUSED(out0)
    Q_UNUSED(out1)

    return outputs;
  };

  static std::bitset<inputLayerSize>
  doubleToBitset(const std::vector<double> &inputs) {
    std::bitset<inputLayerSize> outputs{0};

    outputs.set(0, std::round(inputs[0]));
    outputs.set(1, std::round(inputs[1]));

    return outputs;
  };

  static std::vector<double>
  bitsetToDouble(const std::bitset<inputLayerSize> &inputs) {
    std::vector<double> outputs;

    outputs.push_back(inputs[0]);
    outputs.push_back(inputs[1]);

    return outputs;
  };

  static bool test(std::vector<double> &inputValues,
                   Core::NodeNetwork::NeuralNetwork<double> *neuralNetwork,
                   const bool learn, const bool debug) {

    const std::vector<Core::NodeNetwork::Neuron<double> *> &inputLayer =
        neuralNetwork->layer(0)->neurons();
    const std::vector<Core::NodeNetwork::Neuron<double> *> &outputLayer =
        neuralNetwork->layer(neuralNetwork->layerCount() - 1)->neurons();

    // set test values
    for (unsigned long neuronIdx = 0; neuronIdx < inputLayer.size();
         ++neuronIdx) {
      inputLayer[neuronIdx]->setValue(inputValues[neuronIdx]);
    }

    // activate
    for (auto *neuron : outputLayer) {
      neuron->activate();
    }

    auto desired = desiredOutputs(doubleToBitset(inputValues));

    // show debug info
    if (debug) {
      //      std::cout << "pre-update:\n";
      //      Print::printWeights(layerConnections);
      //      Print::printBiases(layerNeurons);
      //      Print::printActivations(layerNeurons);
      //      Print::printSensitivities(layerNeurons);
      //      Print::printErrors(outputLayer, desired);
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

      // show debug info
      if (debug) {
        //        std::cout << "post-update:\n";
        //        Print::printWeights(layerConnections);
        //        Print::printBiases(layerNeurons);
        //        Print::printActivations(layerNeurons);
        //        Print::printSensitivities(layerNeurons);
        //        Print::printErrors(outputLayer, desired);
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

  static bool test(std::bitset<inputLayerSize> &inputValues,
                   Core::NodeNetwork::NeuralNetwork<double> *neuralNetwork,
                   const bool learn, const bool debug) {

    auto inputs = bitsetToDouble(inputValues);
    return test(inputs, neuralNetwork, learn, debug);
  }

  static double testSet(Core::NodeNetwork::NeuralNetwork<double> *neuralNetwork,
                        const bool learn, const bool debug) {

    const std::vector<Core::NodeNetwork::Neuron<double> *> &inputLayer =
        neuralNetwork->layer(0)->neurons();

    unsigned long long kTestingIterations = std::pow(2, inputLayer.size());
    unsigned long long correctCount = 0;

    for (unsigned long long i = 0; i < kTestingIterations; ++i) {

      std::bitset<inputLayerSize> inputValues{i};

      // run test
      bool correct = test(inputValues, neuralNetwork, learn, debug);
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

  static void
  learnFromInputSets(Core::NodeNetwork::NeuralNetwork<double> *neuralNetwork,
                     const bool debug) {
    std::vector<double> accuracies;

    for (unsigned long long i = 0; i < kLearningIterations; ++i) {
      if (i % kLearnPoll == 0) {
        // test the current weights without updating the network.
        double accuracy = testSet(neuralNetwork, true, true);
        accuracies.push_back(accuracy);
      } else {
        // teach the network
        double accuracy = testSet(neuralNetwork, true, false);
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

  static void learnFromRandomBoolInputs(
      Core::NodeNetwork::NeuralNetwork<double> *neuralNetwork,
      const bool debug) {
    unsigned long long correctCount = 0;
    std::vector<double> accuracies;

    std::bitset<inputLayerSize> inputs = {0};
    for (unsigned long long i = 0; i < kLearningIterations * 4; ++i) {
      for (unsigned long long nodeIdx = 0; nodeIdx < inputs.size(); ++nodeIdx) {
        inputs.set(nodeIdx, rand() % 2);
      }

      if (i != 0 && i % kLearnPoll == 0) {
        double accuracy = 100.0 * correctCount / kLearnPoll;
        accuracies.push_back(accuracy);
        correctCount = 0;
        bool correct = test(inputs, neuralNetwork, true, true);
        if (correct) {
          ++correctCount;
        }
      } else {
        // teach the network
        bool correct = test(inputs, neuralNetwork, true, false);
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

  static void
  learnFromRandomInputs(Core::NodeNetwork::NeuralNetwork<double> *neuralNetwork,
                        const bool debug) {
    unsigned long long correctCount = 0;
    std::vector<double> accuracies;

    std::vector<double> inputs;
    for (unsigned long long i = 0; i < kLearningIterations * 4; ++i) {
      for (unsigned long long nodeIdx = 0; nodeIdx < inputLayerSize;
           ++nodeIdx) {
        inputs.push_back(static_cast<double>(rand()) / RAND_MAX);
      }

      if (i != 0 && i % kLearnPoll == 0) {
        double accuracy = 100.0 * correctCount / kLearnPoll;
        accuracies.push_back(accuracy);
        correctCount = 0;
        bool correct = test(inputs, neuralNetwork, true, true);
        if (correct) {
          ++correctCount;
        }
      } else {
        // teach the network
        bool correct = test(inputs, neuralNetwork, true, false);
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
  srand(3);

  Shared::NodeNetwork::NodeNetworkFactory factory =
      Shared::NodeNetwork::NodeNetworkFactory();
  Shared::NodeNetwork::AbstractNodeNetwork *abstractNet =
      factory.createMeshNetwork<Core::NodeNetwork::NeuralNetwork<double>>(
          {2, 2, 2});
  Core::NodeNetwork::NeuralNetwork<double> *neuralNet =
      static_cast<Core::NodeNetwork::NeuralNetwork<double> *>(abstractNet);

  // teach the network
  Test::learnFromRandomInputs(neuralNet, true);

  // UI
  //=========================================================================
  QApplication a(argc, argv);
  UI::Application::Application application = UI::Application::Application();

  application.view()->show();

  return a.exec();
}
