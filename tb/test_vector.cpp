#include "test_vector.h"
#include "ostream_utils.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace tb {

// Optimized line ending to std::endl (without std::flush)
static const std::string EOL{"\n"};

void test_vector::load(const std::string& line)
{
    std::istringstream iss(line);

    if (verbose)
    {
        std::cerr << "parsing..." << EOL;
        std::cerr << line << EOL;
    }

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

    if (is.fail())
    {
        throw std::runtime_error("invalid test vector format");
    }

    if (verbose)
        std::cerr << "<bx=" << bx << ">" << EOL;
}

void test_vector::load_muons(std::istream& is)
{
    for (size_t i = 0; i < muon_size; ++i)
    {
        byte_vector data = next(is);

        auto& muon = in_data.muon[i];
        muon.phi = data.slice(0, 9);
        muon.pt = data.slice(10, 18);
        muon.qual = data.slice(19, 22);
        muon.eta = data.slice(23, 31);
        muon.iso = data.slice(32, 33);
        muon.charge = data.slice(34, 35);

        if (verbose)
            std::cerr << muon << EOL;
    }
}

void test_vector::load_egammas(std::istream& is)
{
    for (size_t i = 0; i < egamma_size; ++i)
    {
        byte_vector data = next(is);

        auto& egamma = in_data.eg[i];
        egamma.pt = data.slice(0, 8);
        egamma.eta = data.slice(9, 16);
        // egamma.phi = data.slice(17, 24);
        // egamma.iso = data.slice(25, 26);

        if (verbose)
            std::cerr << egamma << EOL;
    }
}

void test_vector::load_taus(std::istream& is)
{
    for (size_t i = 0; i < tau_size; ++i)
    {
        byte_vector data = next(is);

        auto& tau = in_data.tau[i];
        tau.pt = data.slice(0, 8);
        tau.eta = data.slice(9, 16);
        // tau.phi = data.slice(17, 24);
        // tau.iso = data.slice(25, 26);

        if (verbose)
            std::cerr << tau << EOL;
    }
}

void test_vector::load_jets(std::istream& is)
{
    for (size_t i = 0; i < jet_size; ++i)
    {
        byte_vector data = next(is);

        auto& jet = in_data.jet[i];
        jet.pt = data.slice(0, 10);
        jet.eta = data.slice(11, 18);
        // jet.phi = data.slice(19, 26);

        if (verbose)
            std::cerr << jet << EOL;
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
    assert(algorithms.data.size() == (algorithm_size / byte_vector::byte_bits));
    if (verbose)
        std::cerr << "<algorithms=0x" << algorithms << ">" << EOL;
}

void test_vector::load_finor(std::istream& is)
{
    byte_vector data = next(is);
    finor = data.test(0);

    if (verbose)
        std::cerr << "<finor=0x" << finor << ">" << EOL;
}

byte_vector test_vector::next(std::istream& is)
{
    std::string s;
    is >> s;

    if (is.fail())
    {
        throw std::runtime_error("invalid data format");
    }

    return byte_vector(s);
}

} // namespace tb
