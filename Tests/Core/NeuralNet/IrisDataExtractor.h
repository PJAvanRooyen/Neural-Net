#ifndef DataExtractor_H
#define DataExtractor_H

#include <QDir>
#include <QRegularExpressionMatch>
#include <algorithm>
#include <fstream>
#include <random>
#include <vector>

namespace Tests {
namespace DataExtractor {

class Iris {
public:
  enum Type : unsigned { Setosa = 0, Versicolour = 1, Virginica = 2 };

  Iris(const Type type, const double sepalLength, const double sepalWidth,
       const double pedalLength, const double pedalWidth)
      : mType(type), mSepalLength(sepalLength), mSepalWidth(sepalWidth),
        mPedalLength(pedalLength), mPedalWidth(pedalWidth){};

  std::vector<double> information() const {
    return {mSepalLength, mSepalWidth, mPedalLength, mPedalWidth};
  }

  std::vector<double> classification() const {
    std::vector<double> typeToBools(3, 0.0);

    typeToBools[mType] = 1.0;
    return typeToBools;
  }

  Type mType;

  double mSepalLength;
  double mSepalWidth;
  double mPedalLength;
  double mPedalWidth;
};

class DataExtractor {
public:
  DataExtractor();

  ~DataExtractor();

  static std::vector<Iris> extract() {
    QDir proj = QDir::current();
    proj.cdUp();
    proj.cd("Thirdparty/Imports/Datasets/Iris");
    QString fileDir = proj.absolutePath();
    QFileInfo file = QFileInfo(fileDir, "iris.data");

    const QString kIrisDataFile(file.absoluteFilePath());

    // example: 5.1,3.5,1.4,0.2,Iris-setosa
    const QRegularExpression kIrisMatcher(
        "^(?P<sepalLength>[0-9.]*),(?P<sepalWidth>[0-9.]*),(?P<pedalLength>[0-"
        "9.]*),(?P<pedalWidth>[0-9.]*),Iris-(?P<type>[a-z]*)$",
        QRegularExpression::PatternOption::CaseInsensitiveOption);

    std::ifstream ifs(kIrisDataFile.toStdString(), std::ios_base::in);
    if (!ifs.good()) {
      return {};
    }

    std::vector<Iris> irises;
    for (std::string line; std::getline(ifs, line);) {
      if (line.empty()) {
        break;
      }

      QRegularExpressionMatch match =
          kIrisMatcher.match(QString::fromStdString(line));

      if (!match.hasMatch()) {
        continue;
      }

      std::string typeStr = match.captured("type").toStdString();
      double sepalLength = match.captured("sepalLength").toDouble();
      double sepalWidth = match.captured("sepalWidth").toDouble();
      double pedalLength = match.captured("pedalLength").toDouble();
      double pedalWidth = match.captured("pedalWidth").toDouble();

      Iris::Type type = Iris::Type::Setosa;
      if (typeStr == "setosa") {
        type = Iris::Type::Setosa;
      } else if (typeStr == "versicolor") {
        type = Iris::Type::Versicolour;
      } else if (typeStr == "virginica") {
        type = Iris::Type::Virginica;
      }

      irises.push_back(
          Iris(type, sepalLength, sepalWidth, pedalLength, pedalWidth));
    }
    return irises;
  }

  std::pair<
      std::vector<double> /*inputs*/,
      std::vector<
          double> /*desiredOutputs*/> static getRandomDatapoint(std::vector<Iris>
                                                                    &inputSet,
                                                                const unsigned long
                                                                    inputNodeCount) {
    std::pair<std::vector<double> /*inputs*/,
              std::vector<double> /*desiredOutputs*/>
        datapoint;
    datapoint.first.reserve(inputNodeCount);

    auto randomInputSetIndex = std::round(
        (static_cast<double>(rand()) / RAND_MAX) * (inputSet.size() - 1));

    Iris iris = inputSet[randomInputSetIndex];
    auto data = iris.information();
    for (unsigned long nodeIdx = 0; nodeIdx < inputNodeCount; ++nodeIdx) {
      datapoint.first.push_back(data[nodeIdx]);
    }

    datapoint.second = iris.classification();
    return datapoint;
  };

  static void generateLearningAndTestingSets(
      std::vector<std::pair<std::vector<double> /*inputs*/,
                            std::vector<double> /*desiredOutputs*/>>
          &learningSet,
      std::vector<std::pair<std::vector<double> /*inputs*/,
                            std::vector<double> /*desiredOutputs*/>>
          &testingSet,
      const unsigned long inputNodeCount,
      const unsigned long learningIterations,
      const unsigned long testingIterations) {

    //
    // amount of learning relative to testing data.
    double learnFraction = static_cast<double>(learningIterations) /
                           (learningIterations + testingIterations);

    // get the data
    auto irisData = DataExtractor::DataExtractor::extract();
    // split into sets for each output type
    std::vector<Iris> setosa;
    std::vector<Iris> versicolour;
    std::vector<Iris> virginica;
    setosa.insert(setosa.begin(), irisData.cbegin(), irisData.cbegin() + 50);
    versicolour.insert(versicolour.begin(), irisData.cbegin() + 50,
                       irisData.cbegin() + 100);
    virginica.insert(virginica.begin(), irisData.cbegin() + 100,
                     irisData.cbegin() + 150);

    // randomly shuffle the data
    std::random_shuffle(setosa.begin(), setosa.end());
    std::random_shuffle(versicolour.begin(), versicolour.end());
    std::random_shuffle(virginica.begin(), virginica.end());

    // create the learning set
    std::vector<Iris> learnSet;
    learnSet.insert(learnSet.begin(), setosa.cbegin(),
                    setosa.cbegin() +
                        std::round(setosa.size() * learnFraction));
    learnSet.insert(learnSet.end(), versicolour.cbegin(),
                    versicolour.cbegin() +
                        std::round(versicolour.size() * learnFraction));
    learnSet.insert(learnSet.end(), virginica.cbegin(),
                    virginica.cbegin() +
                        std::round(virginica.size() * learnFraction));

    for (unsigned long idx = 0; idx < learningIterations; ++idx) {
      std::pair<std::vector<double> /*inputs*/,
                std::vector<double> /*desiredOutputs*/>
          datapoint = getRandomDatapoint(learnSet, inputNodeCount);
      learningSet.push_back(datapoint);
    }

    // create the testing set
    std::vector<Iris> testSet;
    testSet.insert(testSet.begin(),
                   setosa.cbegin() + std::round(setosa.size() * learnFraction),
                   setosa.cend());
    testSet.insert(testSet.end(),
                   versicolour.cbegin() +
                       std::round(versicolour.size() * learnFraction),
                   versicolour.cend());
    testSet.insert(testSet.end(),
                   virginica.cbegin() +
                       std::round(virginica.size() * learnFraction),
                   virginica.cend());

    for (unsigned long idx = 0; idx < testingIterations; ++idx) {
      std::pair<std::vector<double> /*inputs*/,
                std::vector<double> /*desiredOutputs*/>
          datapoint = getRandomDatapoint(testSet, inputNodeCount);
      testingSet.push_back(datapoint);
    }
  }
};

} // namespace DataExtractor
} // namespace Tests

#endif // DataExtractor_H
