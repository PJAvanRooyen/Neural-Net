#ifndef VariadicTemplate_H
#define VariadicTemplate_H

#include <QString>
#include <QtGlobal>
#include <string>
#include <type_traits>
#include <vector>

namespace Example {

class ClassExample {
public:
  explicit ClassExample(const QString &string) : mString(string) {}
  QString string() { return mString; }

private:
  QString mString;
};

enum EnumExample {
  Ten = 10,
  Eleven = 11,
};

class VariadicTemplate {
public:
  VariadicTemplate(QString &inputString);

  ~VariadicTemplate() = default;

private:
  /*!
   * \details handle list that contains a trivial type.
   */
  template <typename T, typename... Arg,
            std::enable_if_t<std::is_trivial_v<T>> * = nullptr>
  void appendToString(const T value, const Arg... args) {
    appendToString(value);
    appendToString(args...);
  }

  /*!
   * \details handle list that contains a vector of chars.
   */
  template <typename T, typename... Arg,
            std::enable_if_t<std::is_same_v<std::vector<unsigned char>, T>> * =
                nullptr>
  void appendToString(const T vec, const Arg... args) {
    appendToString(vec);
    appendToString(args...);
  }

  /*!
   * \details handle list that contains a string.
   */
  template <typename T, typename... Arg,
            std::enable_if_t<std::is_same_v<std::string, T>> * = nullptr>
  void appendToString(const T string, const Arg... args) {
    appendToString(string);
    appendToString(args...);
  }

  /*!
   * \details handle list that contains a qByteArray
   */
  template <typename T, typename... Arg,
            std::enable_if_t<std::is_same_v<QByteArray, T>> * = nullptr>
  void appendToString(const T qByteArray, const Arg... args) {
    appendToString(qByteArray);
    appendToString(args...);
  }

  /*!
   * \details handle list that contains a newly defined class.
   */
  template <typename T, typename... Arg,
            std::enable_if_t<std::is_same_v<ClassExample, T>> * = nullptr>
  void appendToString(const T classExample, const Arg... args) {
    appendToString(classExample);
    appendToString(args...);
  }

  /*!
   * \details handle trivial types.
   */
  template <typename T, std::enable_if_t<std::is_trivial_v<T>> * = nullptr>
  void appendToString(const T value) {
    mString += QString::number(value);
  }

  /*!
   * \details handle a vector of chars.
   */
  template <typename T,
            std::enable_if_t<std::is_same_v<std::vector<unsigned char>, T>> * =
                nullptr>
  void appendToString(T vec) {
    for (char charItem : vec) {
      mString.append(charItem);
    }
  }

  /*!
   * \details handle a string.
   */
  template <typename T,
            std::enable_if_t<std::is_same_v<std::string, T>> * = nullptr>
  void appendToString(T string) {
    mString.append(QString::fromStdString(string));
  }

  /*!
   * \details handle a QByteArray
   */
  template <typename T,
            std::enable_if_t<std::is_same_v<QByteArray, T>> * = nullptr>
  void appendToString(T qByteArray) {
    mString.append(QString::fromStdString(qByteArray.toStdString()));
  }

  /*!
   * \details handle a newly defined class
   */
  template <typename T,
            std::enable_if_t<std::is_same_v<ClassExample, T>> * = nullptr>
  void appendToString(T classExample) {
    mString.append(classExample.string());
  }

  QString &mString;
};

} // namespace Example
#endif // VariadicTemplate_H
