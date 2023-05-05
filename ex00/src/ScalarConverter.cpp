#include "ScalarConverter.hpp"

#include <climits>
#include <iomanip>
#include <iostream>

/* ==============================================
 *               Convert functions
 * ============================================== */
void ScalarConverter::convert(std::string const& literal) {
  // Detect the type of literal ( char/int/float/double )
  enum LiteralType type = detectLiteralType(literal);
  switch (type) {
    case CHAR_LITERAL: {
      char c = literal[0];
      printChar(c);
      printInt(static_cast<int>(c));
      printFloat(static_cast<float>(c));
      printDouble(static_cast<double>(c));
      break;
    }
    case INT_LITERAL: {
      int i = std::stoi(literal);
      if (i < CHAR_MIN || i > CHAR_MAX) {
        std::cout << "char: "
                  << "impossible" << std::endl;
      } else {
        printChar(static_cast<char>(i));
      }
      printInt(i);
      printFloat(static_cast<float>(i));
      printDouble(static_cast<double>(i));
      break;
    }
    case FLOAT_LITERAL: {
      std::size_t i;
      float f = std::stof(literal, &i);
      // Check if conversion is successful, i.e. the whole string is converted.
      // The last character should be 'f' or 'F' for float.
      if (i != literal.length() - 1) {
        throw ScalarConverter::ConversionError("Invalid float literal: " +
                                               literal);
      }
      if (f < CHAR_MIN || f > CHAR_MAX) {
        std::cout << "char: "
                  << "impossible" << std::endl;
      } else {
        printChar(static_cast<char>(f));
      }
      if (static_cast<double>(f) < INT_MIN ||
          static_cast<double>(f) > INT_MAX) {
        std::cout << "int: "
                  << "impossible" << std::endl;
      } else {
        printInt(static_cast<int>(f));
      }
      printFloat(f);
      printDouble(static_cast<double>(f));
      break;
    }
    case DOUBLE_LITERAL: {
      std::size_t i;
      double d = std::stod(literal, &i);
      if (i != literal.length()) {
        throw ScalarConverter::ConversionError("Invalid double literal: " +
                                               literal);
      }
      if (d < CHAR_MIN || d > CHAR_MAX) {
        std::cout << "char: "
                  << "impossible" << std::endl;
      } else {
        printChar(static_cast<char>(d));
      }
      if (d < INT_MIN || d > INT_MAX) {
        std::cout << "int: "
                  << "impossible" << std::endl;
      } else {
        printInt(static_cast<int>(d));
      }
      // Overflow or underflow can be handled as inff or -inff
      printFloat(static_cast<float>(d));
      printDouble(d);
      break;
    }
    default: {
      throw ScalarConverter::ConversionError("Invalid literal type: " +
                                             literal);
    }
  }
}

/* ==============================================
 *               Helper functions
 * ============================================== */
void ScalarConverter::printChar(char c) {
  if (isprint(c)) {
    std::cout << "char: "
              << "'" << c << "'" << std::endl;
  } else {
    std::cout << "char: "
              << "Non displayable" << std::endl;
  }
}

void ScalarConverter::printInt(int i) {
  std::cout << "int: " << i << std::endl;
}

void ScalarConverter::printFloat(float f) {
  std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f"
            << std::endl;
}

void ScalarConverter::printDouble(double d) {
  std::cout << "double: " << std::fixed << std::setprecision(1) << d
            << std::endl;
}

enum LiteralType ScalarConverter::detectLiteralType(
    std::string const& literal) {
  if (literal.length() == 0) {
    return NOSUCHTYPE_LITERAL;
  }
  // Check if it is a char
  if (literal.length() == 1 && !isdigit(literal[0])) {
    return CHAR_LITERAL;
  }
  // Check if float special values: nanf, inff, -inff, +inff
  if (literal == "nanf" || literal == "inff" || literal == "-inff" ||
      literal == "+inff") {
    return FLOAT_LITERAL;
  }
  // Check if double special values: nan, inf, -inf, +inf
  if (literal == "nan" || literal == "inf" || literal == "-inf" ||
      literal == "+inf") {
    return DOUBLE_LITERAL;
  }
  // Check if it is a float
  // "only the decimal notation will be used."
  // We can ignore e-notation.
  // The float literal must end with the character f.
  if (literal[literal.length() - 1] == 'f') {
    return FLOAT_LITERAL;
  }
  // Check if it is a double
  // "only the decimal notation will be used."
  // We can ignore e-notation.
  // The double literal must contains a decimal point.
  if (literal.find('.') != std::string::npos) {
    return DOUBLE_LITERAL;
  }
  // Check if it is an int
  size_t i = 0;
  if (literal[0] == '-' || literal[0] == '+') {
    if (literal.length() == 1) {
      return NOSUCHTYPE_LITERAL;
    }
    i++;
  }
  for (; i < literal.length(); i++) {
    char c = literal[i];
    if (!isdigit(c)) {
      return NOSUCHTYPE_LITERAL;
    }
  }
  return INT_LITERAL;
}

/* ==============================================
 *                   Exceptions
 * ============================================== */
const char* ScalarConverter::ConversionError::what() const throw() {
  return msg_.c_str();
}

ScalarConverter::ConversionError::ConversionError(
    std::string const& msg) throw()
    : msg_(msg) {}

ScalarConverter::ConversionError::~ConversionError() throw() {}
