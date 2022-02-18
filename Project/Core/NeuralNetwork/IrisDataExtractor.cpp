#include "IrisDataExtractor.h"

namespace Core {
namespace DataExtractor {

Iris::Iris(const Iris::Type type, const double sepalLength,
           const double sepalWidth, const double pedalLength,
           const double pedalWidth)
    : mType(type), mSepalLength(sepalLength), mSepalWidth(sepalWidth),
      mPedalLength(pedalLength), mPedalWidth(pedalWidth) {}

Iris::Iris()
    : mType(Setosa), mSepalLength(0), mSepalWidth(0), mPedalLength(0),
      mPedalWidth(0) {
  Q_ASSERT(false);
}

void Iris::information(std::vector<double> &inputs) const {
  inputs = {mSepalLength, mSepalWidth, mPedalLength, mPedalWidth};
}

void Iris::classification(std::vector<double> &outputs) const {
  outputs.assign({0, 0, 0});

  if (mType > outputs.size()) {
    Q_ASSERT(false);
  }
  outputs[mType] = 1.0;
}

DataExtractor::DataExtractor() {}

void DataExtractor::extract(std::vector<Iris> &irisData) {
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

    const auto iris =
        Iris(type, sepalLength, sepalWidth, pedalLength, pedalWidth);
    irisData.push_back(iris);
  }

  Q_ASSERT(irisData.size() == 150);
}

void DataExtractor::getRandomDatapoint(
    std::vector<Iris> &inputSet, const unsigned long inputNodeCount,
    std::pair<std::vector<double>, std::vector<double>> &datapoint) {
  auto randomInputSetIndex = std::round(
      (static_cast<double>(rand()) / RAND_MAX) * (inputSet.size() - 1));

  Q_ASSERT(inputSet.size() > randomInputSetIndex);
  Iris iris = inputSet[randomInputSetIndex];
  std::vector<double> inputs;
  inputs.reserve(inputNodeCount);
  iris.information(inputs);
  for (unsigned long nodeIdx = 0; nodeIdx < inputNodeCount; ++nodeIdx) {
    datapoint.first.push_back(inputs[nodeIdx]);
  }

  iris.classification(datapoint.second);
}

void DataExtractor::generateLearningAndTestingSets(
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &learningSet,
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &testingSet,
    const unsigned long inputNodeCount, const unsigned long outputNodeCount,
    const unsigned long learningIterations,
    const unsigned long testingIterations) {

  // get the data
  std::vector<Iris> irisData;
  irisData.reserve(150);
  extract(irisData);

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
  learnSet.insert(learnSet.begin(), setosa.cbegin(),
                  setosa.cbegin() + learnSubsetEnd);
  learnSet.insert(learnSet.end(), versicolour.cbegin(),
                  versicolour.cbegin() + learnSubsetEnd);
  learnSet.insert(learnSet.end(), virginica.cbegin(),
                  virginica.cbegin() + learnSubsetEnd);

  for (unsigned long idx = 0; idx < learningIterations; ++idx) {
    std::pair<std::vector<double> /*inputs*/,
              std::vector<double> /*desiredOutputs*/>
        datapoint;
    datapoint.first.reserve(inputNodeCount);
    datapoint.second.reserve(outputNodeCount);
    getRandomDatapoint(learnSet, inputNodeCount, datapoint);
    learningSet.push_back(datapoint);
  }

  // create the testing set
  std::vector<Iris> testSet;
  testSet.reserve((setosa.size() - learnSubsetEnd) * 3);
  testSet.insert(testSet.begin(), setosa.cbegin() + learnSubsetEnd,
                 setosa.cend());
  testSet.insert(testSet.end(), versicolour.cbegin() + learnSubsetEnd,
                 versicolour.cend());
  testSet.insert(testSet.end(), virginica.cbegin() + learnSubsetEnd,
                 virginica.cend());

  for (unsigned long idx = 0; idx < testingIterations; ++idx) {
    std::pair<std::vector<double> /*inputs*/,
              std::vector<double> /*desiredOutputs*/>
        datapoint;
    datapoint.first.reserve(inputNodeCount);
    datapoint.second.reserve(outputNodeCount);
    getRandomDatapoint(testSet, inputNodeCount, datapoint);
    testingSet.push_back(datapoint);
  }
}

} // namespace DataExtractor
} // namespace Core
