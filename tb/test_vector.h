#ifndef tb_test_vector_h
#define tb_test_vector_h

#include "../src/definitions.h"
#include "../src/obj.h"

#include "byte_vector.h"

#include <iostream>
#include <string>

namespace tb {

struct test_vector
{
    // test vector format (might differ from actual object counts)
    static const size_t muon_size = 8;
    static const size_t egamma_size = 12;
    static const size_t tau_size = 12;
    static const size_t jet_size = 12;
    static const size_t other_size = 13;
    static const size_t algorithm_size = 512;

    size_t bx;

    in_data_t in_data = {};

    byte_vector algorithms;
    bool finor;

    bool verbose = true;

    void load(const std::string& line);

    void load_bx(std::istream& is);
    void load_muons(std::istream& is);
    void load_egammas(std::istream& is);
    void load_taus(std::istream& is);
    void load_jets(std::istream& is);
    void load_others(std::istream& is);
    void load_algorithms(std::istream& is);
    void load_finor(std::istream& is);

    byte_vector next(std::istream& is);
};

} // namespace tb

#endif
