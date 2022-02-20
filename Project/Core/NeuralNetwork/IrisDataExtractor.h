#ifndef DataExtractor_H
#define DataExtractor_H

#include <vector>

namespace Core {
namespace DataExtractor {

class Iris {
public:
  enum Type : unsigned { Setosa = 0, Versicolour = 1, Virginica = 2 };

  Iris(const Type type, const double sepalLength, const double sepalWidth,
       const double pedalLength, const double pedalWidth);

  const std::pair<std::vector<double>, std::vector<double>> &data() const;

  std::pair<std::vector<double>, std::vector<double>> mData;
};

class DataExtractor {
public:
  DataExtractor();

  static void
  extract(std::vector<std::pair<std::vector<double>, std::vector<double>>>
              &irisData);

  static void getRandomDatapoint(
      const std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &inputSet,
      std::pair<std::vector<double>, std::vector<double>> &datapoint);

  static void generateLearningAndTestingSets(
      std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &learningSet,
      std::vector<std::pair<std::vector<double>, std::vector<double>>>
          &testingSet);
};

} // namespace DataExtractor
} // namespace Core

#endif // DataExtractor_H
