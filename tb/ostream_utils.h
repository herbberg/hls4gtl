#ifndef ostream_formats_h
#define ostream_formats_h

#include "../src/gtl/object.h"
#include "byte_vector.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const tb::byte_vector& bv);

std::ostream& operator<<(std::ostream& os, const gtl::object::muon& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::eg& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::tau& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::jet& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::ett& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::htt& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::etm& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::htm& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::ettem& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::etmhf& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_et& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_ht& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_ethf& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_hthf& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::mbt0hfp& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::mbt0hfm& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::mbt1hfp& object);
std::ostream& operator<<(std::ostream& os, const gtl::object::mbt1hfm& object);

#endif
