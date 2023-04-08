#ifndef DATA_HPP
#define DATA_HPP

#include <inttypes.h>

#include <iostream>

class Data {
 public:
  // Orthodox canonical form
  Data();
  Data(const Data& d);
  Data& operator=(const Data& d);
  ~Data();

  // getters
  unsigned char get(std::size_t idx) const;
  // setters
  void set(unsigned char data[8]);

 private:
  unsigned char _data[8];
};

std::ostream& operator<<(std::ostream& os, const Data& d);
uintptr_t serialize(Data* ptr);
Data* deserialize(uintptr_t raw);

#endif
