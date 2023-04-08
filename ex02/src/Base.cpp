#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

Base::~Base() {
#if DEBUG
  std::cout << "[ Base destructor called ]" << std::endl ;
#endif
}

Base* generate(void) {
  int i = rand() % 3;
  if (i == 0) {
    std::cout << "A generated" << std::endl;
    return new A();
  } else if (i == 1) {
    std::cout << "B generated" << std::endl;
    return new B();
  } else {
    std::cout << "C generated" << std::endl;
    return new C();
  }
}

void identify(Base* p) {
  if (dynamic_cast<A*>(p)) {
    std::cout << "A" << std::endl;
  } else if (dynamic_cast<B*>(p)) {
    std::cout << "B" << std::endl;
  } else if (dynamic_cast<C*>(p)) {
    std::cout << "C" << std::endl;
  } else {
    std::cout << "Unknown" << std::endl;
  }
}

void identify(Base& p) {
  // Identify A
  try {
    A& a = dynamic_cast<A&>(p);
    (void)a;
    std::cout << "A" << std::endl;
    return ;
  } catch (std::bad_cast& e) {}
  // Identify B
  try {
    B& b = dynamic_cast<B&>(p);
    (void)b;
    std::cout << "B" << std::endl;
    return ;
  } catch (std::bad_cast& e) {}
  // Identify C
  try {
    C& c = dynamic_cast<C&>(p);
    (void)c;
    std::cout << "C" << std::endl;
    return ;
  } catch (std::bad_cast& e) {}
  // Unknown
  std::cout << "Unknown" << std::endl;
}
