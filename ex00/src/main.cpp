#include <cfloat>
#include <climits>
#include <iomanip>
#include <iostream>

#include "Convert.hpp"

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
    Convert convert;
    convert.run(literal);
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
