#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <iostream>

enum LiteralType {
  CHAR_LITERAL,
  INT_LITERAL,
  FLOAT_LITERAL,
  DOUBLE_LITERAL,
  NOSUCHTYPE_LITERAL
};

enum LiteralType detectLiteralType(std::string const &literal);

class Convert {
 public:
  // Orthodox canonical form
  Convert();
  Convert(const Convert &c);
  Convert &operator=(const Convert &c);
  ~Convert();

  // Member functions
  void run(std::string const &literal) const;

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
  // Helper functions
  static void printChar(char c);
  static void printInt(int i);
  static void printFloat(float f);
  static void printDouble(double d);
  static enum LiteralType detectLiteralType(std::string const &literal);
};
#endif
