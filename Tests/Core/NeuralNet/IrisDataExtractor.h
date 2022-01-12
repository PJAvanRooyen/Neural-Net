#ifndef DataExtractor_H
#define DataExtractor_H

#include <QDir>
#include <QRegularExpressionMatch>
#include <fstream>
#include <vector>

namespace Tests {
namespace DataExtractor {

class Iris {
public:
  enum Type { Setosa, Versicolour, Virginica };

  Iris(const Type type, const double sepalLength, const double sepalWidth,
       const double pedalLength, const double pedalWidth)
      : mType(type), mSepalLength(sepalLength), mSepalWidth(sepalWidth),
        mPedalLength(pedalLength), mPedalWidth(pedalWidth){};

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
      QRegularExpressionMatch match =
          kIrisMatcher.match(QString::fromStdString(line));

      if (!match.hasMatch()) {
        return {};
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
};

} // namespace DataExtractor
} // namespace Tests

#endif // DataExtractor_H
