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
        mPedalLength(pedalLength), mPedalWidth(pedalWidth) {}

  Iris()
      : mType(Setosa), mSepalLength(0), mSepalWidth(0), mPedalLength(0),
        mPedalWidth(0) {
    Q_ASSERT(false);
  }

  //  Iris(const Iris &other)
  //      : mType(other.mType), mSepalLength(other.mSepalLength),
  //        mSepalWidth(other.mSepalWidth), mPedalLength(other.mPedalLength),
  //        mPedalWidth(other.mPedalWidth) {
  //    qt_noop();
  //  }

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
  DataExtractor() {}

  void extract(std::vector<Iris> &irisData) {
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
      return;
    }

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

      irisData.push_back(
          Iris(type, sepalLength, sepalWidth, pedalLength, pedalWidth));
    }
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

    Q_ASSERT(inputSet.size() > randomInputSetIndex);
    Iris iris = inputSet[randomInputSetIndex];
    auto data = iris.information();
    for (unsigned long nodeIdx = 0; nodeIdx < inputNodeCount; ++nodeIdx) {
      datapoint.first.push_back(data[nodeIdx]);
    }

    datapoint.second = iris.classification();
    return datapoint;
  };

  void generateLearningAndTestingSets(
      std::vector<std::pair<std::vector<double> /*inputs*/,
                            std::vector<double> /*desiredOutputs*/>>
          &learningSet,
      std::vector<std::pair<std::vector<double> /*inputs*/,
                            std::vector<double> /*desiredOutputs*/>>
          &testingSet,
      const unsigned long inputNodeCount,
      const unsigned long learningIterations,
      const unsigned long testingIterations) {

    // get the data
    std::vector<Iris> irisData;
    extract(irisData);

    // test
    //    std::vector<Iris> a;
    //    std::vector<Iris> b;
    //    a.push_back(Iris(Iris ::Type::Setosa, 0, 0, 0, 0));
    //    a.push_back(Iris(Iris ::Type::Setosa, 0, 0, 0, 0));
    //    b.assign(a.cbegin(), a.cbegin() + 1);
    // test

    // split into sets for each output type
    std::vector<Iris> setosa;
    std::vector<Iris> versicolour;
    std::vector<Iris> virginica;
    setosa.reserve(50);
    versicolour.reserve(50);
    virginica.reserve(50);
    setosa.assign(irisData.cbegin(), irisData.cbegin() + 50);
    versicolour.assign(irisData.cbegin() + 50, irisData.cbegin() + 100);
    virginica.assign(irisData.cbegin() + 100, irisData.cbegin() + 150);

    // randomly shuffle the data
    std::random_shuffle(setosa.begin(), setosa.end());
    std::random_shuffle(versicolour.begin(), versicolour.end());
    std::random_shuffle(virginica.begin(), virginica.end());

    // create the learning set
    ulong learnSubsetEnd = std::round(setosa.size() * 0.75);
    std::vector<Iris> learnSet;
    learnSet.reserve(learnSubsetEnd * 3);
    learnSet.assign(setosa.cbegin(), setosa.cbegin() + learnSubsetEnd);
    learnSet.assign(versicolour.cbegin(),
                    versicolour.cbegin() + learnSubsetEnd);
    learnSet.assign(virginica.cbegin(), virginica.cbegin() + learnSubsetEnd);

    for (unsigned long idx = 0; idx < learningIterations; ++idx) {
      std::pair<std::vector<double> /*inputs*/,
                std::vector<double> /*desiredOutputs*/>
          datapoint = getRandomDatapoint(learnSet, inputNodeCount);
      learningSet.push_back(datapoint);
    }

    // create the testing set
    std::vector<Iris> testSet;
    testSet.reserve((setosa.size() - learnSubsetEnd) * 3);
    testSet.assign(setosa.cbegin() + learnSubsetEnd, setosa.cend());
    testSet.assign(versicolour.cbegin() + learnSubsetEnd, versicolour.cend());
    testSet.assign(virginica.cbegin() + learnSubsetEnd, virginica.cend());

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
