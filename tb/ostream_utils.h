#ifndef ostream_formats_h
#define ostream_formats_h

#include "../src/obj.h"
#include "byte_vector.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const tb::byte_vector& bv);

std::ostream& operator<<(std::ostream& os, const gtl::object::muon& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::eg& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::tau& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::jet& object);

#endif
