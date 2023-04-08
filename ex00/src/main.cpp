#include <cfloat>
#include <climits>
#include <iomanip>
#include <iostream>

enum LiteralType {
  CHAR_LITERAL,
  INT_LITERAL,
  FLOAT_LITERAL,
  DOUBLE_LITERAL,
  NOSUCHTYPE_LITERAL
};

// char: must be surrounded by single quotes
// int: must be a number
// float: must be followed by f
// double: must contains a decimal point
enum LiteralType detectLiteralType(std::string const &literal) {
  // Check if it is a char
  if (literal.length() == 1 && !isdigit(literal[0])) {
    return CHAR_LITERAL;
  }
  // Check if it is a float
  if (literal[literal.length() - 1] == 'f' || literal == "nan" ||
      literal == "inf" || literal == "-inf") {
    return FLOAT_LITERAL;
  }
  // Check if it is a double
  if (literal.find('.') != std::string::npos || literal == "nan" ||
      literal == "inf" || literal == "-inf") {
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

// Sample Output:
/*
$ ./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0
$./convert nan
char: impossible
int: impossible
float: nanf
double: nan
$./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
*/
void printChar(char c) {
  if (isprint(c)) {
    std::cout << "char: "
              << "'" << c << "'" << std::endl;
  } else {
    std::cout << "char: "
              << "Non displayable" << std::endl;
  }
}

void printInt(int i) { std::cout << "int: " << i << std::endl; }

void printFloat(float f) {
  std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f"
            << std::endl;
}

void printDouble(double d) {
  std::cout << "double: " << std::fixed << std::setprecision(1) << d
            << std::endl;
}

void printLiteral(std::string const &literal) {
  // Detect the type of literal ( char/int/float/double )
  enum LiteralType type = detectLiteralType(literal);
  switch (type) {
    case CHAR_LITERAL: {
      char c = literal[1];
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
      float f = std::stof(literal);
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
      double d = std::stod(literal);
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
      std::cerr << "Error: "
                << "Invalid literal" << std::endl;
      break;
    }
  }
}

int main(int argc, const char *argv[]) {
  // Validate the command line arguments
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <string representation of literal>"
              << std::endl;
    return 1;
  }

  // Get the command line arguments
  std::string literal = argv[1];

  // Print the literal
  try {
    printLiteral(literal);
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
