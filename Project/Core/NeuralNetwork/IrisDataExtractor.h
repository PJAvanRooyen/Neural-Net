#ifndef DataExtractor_H
#define DataExtractor_H

#include <QDir>
#include <QRegularExpressionMatch>
#include <algorithm>
#include <fstream>
#include <random>
#include <vector>

namespace Core {
namespace DataExtractor {

class Iris {
public:
  enum Type : unsigned { Setosa = 0, Versicolour = 1, Virginica = 2 };

  Iris(const Type type, const double sepalLength, const double sepalWidth,
       const double pedalLength, const double pedalWidth);

  Iris();

  std::vector<double> information() const;

  std::vector<double> classification() const;

  Type mType;

  double mSepalLength;
  double mSepalWidth;
  double mPedalLength;
  double mPedalWidth;
};

class DataExtractor {
public:
  DataExtractor();

  static void extract(std::vector<Iris> &irisData);

  static std::pair<std::vector<double> /*inputs*/,
                   std::vector<double> /*desiredOutputs*/>
  getRandomDatapoint(std::vector<Iris> &inputSet,
                     const unsigned long inputNodeCount);

  static void generateLearningAndTestingSets(
      std::vector<std::pair<std::vector<double> /*inputs*/,
                            std::vector<double> /*desiredOutputs*/>>
          &learningSet,
      std::vector<std::pair<std::vector<double> /*inputs*/,
                            std::vector<double> /*desiredOutputs*/>>
          &testingSet,
      const unsigned long inputNodeCount,
      const unsigned long learningIterations,
      const unsigned long testingIterations);
};

} // namespace DataExtractor
} // namespace Core

#endif // DataExtractor_H
