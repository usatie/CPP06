#include "Data.hpp"

#include <iomanip>
#include <iostream>

Data::Data() : _data() {
#ifdef DEBUG
  std::cout << "[ Data Default constructor called ]" << std::endl;
#endif
}

Data::Data(const Data& d) {
#ifdef DEBUG
  std::cout << "[ Data Copy constructor called ]" << std::endl;
#endif
  for (int i = 0; i < 8; i++) {
    _data[i] = d._data[i];
  }
}

Data& Data::operator=(const Data& d) {
#ifdef DEBUG
  std::cout << "[ Data Copy assignment operator called ]" << std::endl;
#endif
  if (this != &d) {
    for (int i = 0; i < 8; i++) {
      _data[i] = d._data[i];
    }
  }
  return *this;
}

Data::~Data() {
#ifdef DEBUG
  std::cout << "[ Data destructor called ]" << std::endl;
#endif
}

void Data::set(unsigned char const data[8]) {
  for (int i = 0; i < 8; i++) {
    _data[i] = data[i];
  }
}

unsigned char Data::get(std::size_t idx) const {
  if (idx < 8) {
    return _data[idx];
  }
  std::cout << "Error: index out of range" << std::endl;
  return 0;
}

std::ostream& operator<<(std::ostream& os, const Data& d) {
  os << "[ ";
  for (int i = 0; i < 8; i++) {
    os << std::hex << (unsigned int)d.get(i) << " ";
  }
  os << "]";
  return os;
}
