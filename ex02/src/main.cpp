#include <iomanip>
#include <iostream>
#include <cstdlib>

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

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
  // Test identify from pointer
  {
    printSubtitle("Test identify from pointer");
    Base* a = new A;
    Base* b = new B;
    Base* c = new C;
    identify(a);
    identify(b);
    identify(c);
    delete a;
    delete b;
    delete c;
  }
  // Test identify from reference
  {
    printSubtitle("Test identify from reference");
    A a;
    B b;
    C c;
    identify(a);
    identify(b);
    identify(c);
  }
  // Test identify from reference 2
  {
    printSubtitle("Test identify from reference 2");
    Base* a = new A;
    Base* b = new B;
    Base* c = new C;
    identify(*a);
    identify(*b);
    identify(*c);
    delete a;
    delete b;
    delete c;
  }
  // Test generate for 10 times
  {
    printSubtitle("Test generate for 10 times");
    for (int i = 0; i < 10; ++i) {
      Base* p = generate();
      identify(p);
      delete p;
    }
  }
}

int main(void) {
  // Set random seed
  srand(time(NULL));
  // Test from subject pdf
  test_from_subject();
  return 0;
}
