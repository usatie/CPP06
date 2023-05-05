#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP
#include <inttypes.h>
#include "Data.hpp"

class Serializer {
	private:
		// To make it static class, should not implement constructor
		Serializer() ;
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};

#endif
