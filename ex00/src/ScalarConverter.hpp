#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>

enum LiteralType {
  CHAR_LITERAL,
  INT_LITERAL,
  FLOAT_LITERAL,
  DOUBLE_LITERAL,
  NOSUCHTYPE_LITERAL
};

class ScalarConverter {
 public:
  // Static functions
  static void convert(std::string const &literal);

  // Exceptions
  class ConversionError : public std::exception {
   public:
    explicit ConversionError(std::string const &msg) throw();
    virtual const char *what() const throw();
    ~ConversionError() throw();

   private:
    std::string msg_;
  };

 private:
  // This is static class, so don't have to implement it
  ScalarConverter();

 private:
  // Helper functions
  static void printChar(char c);
  static void printInt(int i);
  static void printFloat(float f);
  static void printDouble(double d);
  static enum LiteralType detectLiteralType(std::string const &literal);
};
#endif
