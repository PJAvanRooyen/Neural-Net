#include "VariadicTemplate.h"

namespace Example {

VariadicTemplate::VariadicTemplate(QString &inputString)
    : mString(inputString) {
  // usage example
  qint32 trivialType = 1;

  std::vector<unsigned char> charVector = {'2', '3', '4'};

  std::string string = "5";

  unsigned char charData[3] = {'6', '7', '8'};
  QByteArray qByteArray =
      QByteArray::fromRawData(reinterpret_cast<char *>(charData), 3);

  ClassExample classExample = ClassExample("9");

  EnumExample enumExample1 = EnumExample(10);
  EnumExample enumExample2 = EnumExample::Eleven;

  appendToString(trivialType, charVector, string, qByteArray, classExample,
                 enumExample1, enumExample2);

  qt_noop();
}

} // namespace Example
