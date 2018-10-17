#ifndef tb_test_vector_h
#define tb_test_vector_h

#include "../src/definitions.h"
#include "../src/input.h"

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
    static const size_t ett_size = 1;
    static const size_t htt_size = 1;
    static const size_t etm_size = 1;
    static const size_t htm_size = 1;
    static const size_t etmhf_size = 1;
    static const size_t htmhf_size = 1;
    static const size_t other_size = 6;
    static const size_t external_size = 256;
    static const size_t algorithm_size = 512;

    size_t bx;

    in_data_t in_data = {};

    byte_vector externals;
    byte_vector algorithms;
    bool finor;

    bool verbose = true;

    void load(const std::string& line);

    void load_bx(std::istream& is);
    void load_muons(std::istream& is);
    void load_egammas(std::istream& is);
    void load_taus(std::istream& is);
    void load_jets(std::istream& is);
    void load_ett(std::istream& is);
    void load_htt(std::istream& is);
    void load_etm(std::istream& is);
    void load_htm(std::istream& is);
    void load_etmhf(std::istream& is);
    void load_htmhf(std::istream& is);
    void load_others(std::istream& is);
    void load_externals(std::istream& is);
    void load_algorithms(std::istream& is);
    void load_finor(std::istream& is);

    byte_vector next(std::istream& is);
};

} // namespace tb

#endif
