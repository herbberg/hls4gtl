#ifndef ostream_formats_h
#define ostream_formats_h

#include "../src/obj.h"
#include "byte_vector.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const tb::byte_vector& bv);

std::ostream& operator<<(std::ostream& os, const muon_obj_t& jet);
std::ostream& operator<<(std::ostream& os, const eg_obj_t& egamma);
std::ostream& operator<<(std::ostream& os, const tau_obj_t& tau);
std::ostream& operator<<(std::ostream& os, const jet_obj_t& jet);

#endif
