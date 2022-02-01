#ifndef NeuralNetTestHelper_H
#define NeuralNetTestHelper_H

#include "Core/NeuralNetwork/NeuralNetwork.h"
#include "Core/NeuralNetwork/NeuralNetworkLayer.h"

#include <iostream>
#include <vector>

namespace Tests {

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

  static void
  printSensitivities(Core::NodeNetwork::NeuralNetwork<double> &neuralNetwork) {
    double sensitivitySum = 0;
    unsigned long neuronCount = 0;
    const auto &layers = neuralNetwork.layers();

    std::cout << "sensitivities: ";
    for (auto &layer : layers) {
      const auto &neurons = layer->neurons();
      std::cout << "{";
      for (auto &neuron : neurons) {
        const auto sensitivity = neuron->sensitivity();
        sensitivitySum += sensitivity;
        ++neuronCount;
        std::cout << "[" << sensitivity << "],";
      }
      std::cout << "},";
    }
    std::cout << "\nAverage sensitivity = " << sensitivitySum / neuronCount;
    std::cout << "\n";
  };

  //  static double
  //  printErrors(std::vector<Core::NodeNetwork::Neuron<double> *> &outputNodes,
  //              std::bitset<outputLayerSize> desiredValues) {
  //    double mse = 0;

  //    std::cout << "error: ";
  //    for (unsigned long neuronIdx = 0; neuronIdx < outputNodes.size();
  //         ++neuronIdx) {
  //      double error = desiredValues[neuronIdx] -
  //      outputNodes[neuronIdx]->value(); mse += std::pow(error, 2); std::cout
  //      << "(" << error << "),";
  //    }
  //    mse /= outputLayerSize;
  //    std::cout << " MSE = " << mse;
  //    std::cout << "\n";
  //    return mse;
  //  };

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
    for (unsigned long layerIdx = 0; layerIdx < layerConnections.size();
         ++layerIdx) {
      auto &layer = layerConnections[layerIdx];

      std::cout << "{";
      for (unsigned long nodeIdx = 0; nodeIdx < layer.size(); ++nodeIdx) {
        auto &node = layer[nodeIdx];

        std::cout << "[";
        for (unsigned long connectionIdx = 0; connectionIdx < node.size();
             ++connectionIdx) {
          auto &connection = node[connectionIdx];

          std::cout << "(" << connection->weight() << " = "
                    << prevWeights[layerIdx][nodeIdx][connectionIdx] << " + "
                    << Core::NodeNetwork::sLearningRate << "*"
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

    for (unsigned long layerIdx = 0; layerIdx < layerConnections.size();
         ++layerIdx) {
      auto &layer = layerConnections[layerIdx];
      weights[layerIdx].resize(layerConnections[layerIdx].size());

      for (unsigned long nodeIdx = 0; nodeIdx < layer.size(); ++nodeIdx) {
        auto &node = layer[nodeIdx];
        weights[layerIdx][nodeIdx].resize(
            layerConnections[layerIdx][nodeIdx].size());

        for (unsigned long connectionIdx = 0; connectionIdx < node.size();
             ++connectionIdx) {
          auto &connection = node[connectionIdx];

          weights[layerIdx][nodeIdx][connectionIdx] = connection->weight();
        }
      }
    }
    return weights;
  };
};

} // namespace Tests

#endif // NeuralNetTestHelper_H
