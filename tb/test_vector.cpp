#include "test_vector.h"
#include "ostream_utils.h"

#include <iostream>
#include <sstream>
#include <string>

namespace tb {

void test_vector::load(const std::string& line)
{
    std::istringstream iss(line);

    std::cerr << "loading..." << std::endl;
    std::cerr << line << std::endl;

    load_bx(iss);
    load_muons(iss);
    load_egammas(iss);
    load_taus(iss);
    load_jets(iss);
    load_others(iss);
    load_algorithms(iss);
    load_finor(iss);
}

void test_vector::load_bx(std::istream& is)
{
    is >> std::dec;
    is >> bx;
}

void test_vector::load_muons(std::istream& is)
{
    for (size_t i = 0; i < muon_size; ++i)
    {
        byte_vector data = next(is);
        auto& muon = muon_obj[i];
        muon.pt = data.slice(0, 8);
        muon.eta = data.slice(9, 16);
        // skip...
        std::cerr << muon << std::endl;
    }
}

void test_vector::load_egammas(std::istream& is)
{
    for (size_t i = 0; i < egamma_size; ++i)
    {
        byte_vector data = next(is);
        auto& eg = egamma_obj[i];
        eg.pt = data.slice(0, 8);
        eg.eta = data.slice(9, 16);
        // skip...
        std::cerr << eg << std::endl;
    }
}

void test_vector::load_taus(std::istream& is)
{
    for (size_t i = 0; i < tau_size; ++i)
    {
        byte_vector data = next(is);
        auto& tau = tau_obj[i];
        tau.pt = data.slice(0, 10);
        tau.eta = data.slice(11, 18);
        // skip...
        std::cerr << tau << std::endl;
    }
}

void test_vector::load_jets(std::istream& is)
{
    for (size_t i = 0; i < jet_size; ++i)
    {
        byte_vector data = next(is);
        auto& jet = jet_obj[i];
        jet.pt = data.slice(0, 10);
        jet.eta = data.slice(11, 18);
        // skip...
        std::cerr << jet << std::endl;
    }
}

void test_vector::load_others(std::istream& is)
{
    for (size_t i = 0; i < other_size; ++i)
    {
        byte_vector data = next(is);
        // skip...
    }
}

void test_vector::load_algorithms(std::istream& is)
{
    algorithms = next(is);
    assert(algorithms.data.size() == 512/8);
    // skip...
}

void test_vector::load_finor(std::istream& is)
{
    // skip...
}

byte_vector test_vector::next(std::istream& is)
{
    std::string s;
    is >> s;
    return byte_vector(s);
}

} // namespace tb
