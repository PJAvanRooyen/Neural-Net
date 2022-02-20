#include "IrisDataExtractor.h"

#include <QCoreApplication>
#include <QDir>
#include <QRegularExpressionMatch>

#include <algorithm>
#include <fstream>
#include <random>

namespace Core {
namespace DataExtractor {

Iris::Iris(const Iris::Type type, const double sepalLength,
           const double sepalWidth, const double pedalLength,
           const double pedalWidth)
    : mData(std::make_pair(
          std::vector<double>{sepalLength, sepalWidth, pedalLength, pedalWidth},
          std::vector<double>{type == Type::Setosa ? 1.0 : 0.0,
                              type == Type::Versicolour ? 1.0 : 0.0,
                              type == Type::Virginica ? 1.0 : 0.0})) {}

const std::pair<std::vector<double>, std::vector<double>> &Iris::data() const {
  return mData;
}

DataExtractor::DataExtractor() {}

void DataExtractor::extract(
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &irisData) {
  QDir proj = QCoreApplication::applicationDirPath();
  bool ok = proj.cdUp();
  Q_ASSERT(ok);
  ok = ok && proj.cd("Thirdparty/Imports/Datasets/Iris");
  Q_ASSERT_X(ok, Q_FUNC_INFO,
             QString("current dir: %1").arg(proj.absolutePath()).toLatin1());
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
    Q_ASSERT(false);
    return;
  }

  for (std::string line; std::getline(ifs, line);) {
    if (line.empty()) {
      break;
    }

    QRegularExpressionMatch match =
        kIrisMatcher.match(QString::fromStdString(line));

    if (!match.hasMatch()) {
      Q_ASSERT(false);
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
    } else {
      Q_ASSERT(false);
    }

    const auto iris =
        Iris(type, sepalLength, sepalWidth, pedalLength, pedalWidth);
    irisData.push_back(iris.data());
  }

  Q_ASSERT(irisData.size() == 150);
}

void DataExtractor::getRandomDatapoint(
    const std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &inputSet,
    std::pair<std::vector<double>, std::vector<double>> &datapoint) {
  auto randomInputSetIndex = std::round(
      (static_cast<double>(rand()) / RAND_MAX) * (inputSet.size() - 1));

  Q_ASSERT(inputSet.size() > randomInputSetIndex);
  auto &iris = inputSet[randomInputSetIndex];
  datapoint = iris;
}

void DataExtractor::generateLearningAndTestingSets(
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &learningSet,
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        &testingSet) {

  // get the data
  using Dataset =
      std::vector<std::pair<std::vector<double>, std::vector<double>>>;
  Dataset irisData;
  // irisData.reserve(150);
  extract(irisData);
  Q_ASSERT_X(irisData.size() == 150, Q_FUNC_INFO,
             QString("size: %1").arg(irisData.size()).toLatin1());

  // split into sets for each output type
  auto begin = irisData.begin();
  auto end = irisData.begin() + 50;
  Dataset setosa(begin, end);
  begin = end;
  end = irisData.begin() + 100;
  Dataset versicolour(begin, end);
  begin = end;
  end = irisData.begin() + 150;
  Dataset virginica(begin, end);

  // randomly shuffle the data
  std::random_shuffle(setosa.begin(), setosa.end());
  std::random_shuffle(versicolour.begin(), versicolour.end());
  std::random_shuffle(virginica.begin(), virginica.end());

  // create the learning set
  unsigned long learnSubsetEnd = std::round(setosa.size() * 0.75);
  learningSet.reserve(learnSubsetEnd * 3);
  learningSet.insert(learningSet.begin(), setosa.cbegin(),
                     setosa.cbegin() + learnSubsetEnd);
  learningSet.insert(learningSet.end(), versicolour.cbegin(),
                     versicolour.cbegin() + learnSubsetEnd);
  learningSet.insert(learningSet.end(), virginica.cbegin(),
                     virginica.cbegin() + learnSubsetEnd);

  // create the testing set
  testingSet.reserve((setosa.size() - learnSubsetEnd) * 3);
  testingSet.insert(testingSet.begin(), setosa.cbegin() + learnSubsetEnd,
                    setosa.cend());
  testingSet.insert(testingSet.end(), versicolour.cbegin() + learnSubsetEnd,
                    versicolour.cend());
  testingSet.insert(testingSet.end(), virginica.cbegin() + learnSubsetEnd,
                    virginica.cend());
}

} // namespace DataExtractor
} // namespace Core
