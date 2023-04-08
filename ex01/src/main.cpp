#include <iomanip>
#include <iostream>

#include "Data.hpp"

#define RESET "\033[m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BOLD "\033[1m"

// print title in green color surrounded by '='
void printTitle(std::string const& title) {
  // set color to green
  std::cout << GREEN << BOLD;
  // print '='
  std::cout << std::setfill('=') << std::setw(80) << "" << std::endl;
  // print title at the center
  std::cout << std::setfill(' ') << std::setw(40 - title.length() / 2) << ""
            << title << std::endl;
  // print '='
  std::cout << std::setfill('=') << std::setw(80) << "" << std::endl;
  // reset color
  std::cout << RESET << std::setfill(' ') << std::setw(0);
}

// print test subtitle in white color surrounded by '-'
void printSubtitle(std::string const& subtitle) {
  // print '-'
  std::cout << std::setfill('-') << std::setw(80) << "" << std::endl;
  // print subtitle at the center
  std::cout << std::setfill(' ') << std::setw(40 - subtitle.length() / 2) << ""
            << subtitle << std::endl;
  // print '-'
  std::cout << std::setfill('-') << std::setw(80) << "" << std::endl;
  // reset color
  std::cout << RESET << std::setfill(' ') << std::setw(0);
}

void test_from_subject() {
  printTitle("Test from sunject pdf");
  printSubtitle(
      "The return value of deserialize() compares equal to the original "
      "pointer");
  unsigned char data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  Data d;

  d.set(data);
  uintptr_t raw = serialize(&d);
  Data* ptr = deserialize(raw);
  std::cout << "d         : " << d << std::endl;
  std::cout << "raw       : " << raw << std::endl;
  std::cout << "&d        : " << &d << std::endl;
  std::cout << "ptr       : " << ptr << std::endl;
  std::cout << "*ptr      : " << *ptr << std::endl;
  std::cout << "&d == ptr : " << (&d == ptr ? "true" : "false") << std::endl;
}

int main(void) {
  test_from_subject();
  return 0;
}
