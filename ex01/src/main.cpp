#include <iomanip>
#include <iostream>

#include "Data.hpp"
#include "Serializer.hpp"

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
  unsigned char data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  Data d;

  d.set(data);

  printSubtitle("Use serialize() on the address of the Data object and pass its return value to deserialize().");
  {
	  if ( &d == Serializer::deserialize(Serializer::serialize(&d)) ) {
	  	std::cout << GREEN << "the return value of deserialize() is equal to the original pointer." << RESET << std::endl ;
	  } else {
	  	std::cout << RED << "the return value of deserialize() is not equal to the original pointer." << RESET << std::endl ;
	  }
  }

  printSubtitle("Inspect the pointer values");
  {
	  uintptr_t raw = Serializer::serialize(&d);
	  Data* ptr = Serializer::deserialize(raw);
	  std::cout << "d         : " << d << std::endl;
	  std::cout << "raw       : " << raw << std::endl;
	  std::cout << "&d        : " << &d << std::endl;
	  std::cout << "ptr       : " << ptr << std::endl;
	  std::cout << "*ptr      : " << *ptr << std::endl;
	  std::cout << "&d == ptr : " << (&d == ptr ? "true" : "false") << std::endl;
  }
}

int main(void) {
  test_from_subject();
  return 0;
}
