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
    load_ett(iss);
    load_htt(iss);
    load_etm(iss);
    load_htm(iss);
    load_etmhf(iss);
    load_htmhf(iss);
    load_others(iss);
    load_externals(iss);
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
        egamma.phi = data.slice(17, 24);
        egamma.iso = data.slice(25, 26);

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
        tau.phi = data.slice(17, 24);
        tau.iso = data.slice(25, 26);

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
        jet.phi = data.slice(19, 26);

        if (verbose)
            std::cerr << jet << EOL;
    }
}

void test_vector::load_ett(std::istream& is)
{
    byte_vector data = next(is);

    auto& ett = in_data.ett[0];
    ett.pt = data.slice(0, 11);
    auto& ettem = in_data.ettem[0];
    ettem.pt = data.slice(12, 23);
    auto& mbt0hfp = in_data.mbt0hfp[0];
    mbt0hfp.count = data.slice(28, 31);

    if (verbose)
    {
        std::cerr << ett << EOL;
        std::cerr << ettem << EOL;
        std::cerr << mbt0hfp << EOL;
    }
}

void test_vector::load_htt(std::istream& is)
{
    byte_vector data = next(is);

    auto& htt = in_data.htt[0];
    htt.pt = data.slice(0, 11);
//     auto& towercount = in_data.towercount[0];
//     towercount.count = data.slice(12, 24);
    auto& mbt0hfm = in_data.mbt0hfm[0];
    mbt0hfm.count = data.slice(28, 31);

    if (verbose)
    {
        std::cerr << htt << EOL;
        std::cerr << mbt0hfm << EOL;
    }
}

void test_vector::load_etm(std::istream& is)
{
    byte_vector data = next(is);

    auto& etm = in_data.etm[0];
    etm.pt = data.slice(0, 11);
    etm.phi = data.slice(12, 19);
    auto& asymmetry_et = in_data.asymmetry_et[0];
    asymmetry_et.count = data.slice(20, 27);
    auto& mbt1hfp = in_data.mbt1hfp[1];
    mbt1hfp.count = data.slice(28, 31);

    if (verbose)
    {
        std::cerr << etm << EOL;
        std::cerr << asymmetry_et << EOL;
        std::cerr << mbt1hfp << EOL;
    }
}

void test_vector::load_htm(std::istream& is)
{
    byte_vector data = next(is);

    auto& htm = in_data.htm[0];
    htm.pt = data.slice(0, 11);
    htm.phi = data.slice(12, 19);
    auto& asymmetry_ht = in_data.asymmetry_ht[0];
    asymmetry_ht.count = data.slice(20, 27);
    auto& mbt1hfm = in_data.mbt1hfm[0];
    mbt1hfm.count = data.slice(28, 31);

    if (verbose)
    {
        std::cerr << htm << EOL;
        std::cerr << asymmetry_ht << EOL;
        std::cerr << mbt1hfm << EOL;
    }
}

void test_vector::load_etmhf(std::istream& is)
{
    byte_vector data = next(is);

    auto& etmhf = in_data.etmhf[0];
    etmhf.pt = data.slice(0, 11);
    etmhf.phi = data.slice(12, 19);
    auto& asymmetry_ethf = in_data.asymmetry_ethf[0];
    asymmetry_ethf.count = data.slice(20, 27);
    auto& centrality = in_data.centrality;
    for (size_t i = 0; i < 4; ++i)
    {
        centrality[i] = data.slice(28+i, 28+i);
    }

    if (verbose)
    {
        std::cerr << etmhf << EOL;
        std::cerr << asymmetry_ethf << EOL;
    }
}

void test_vector::load_htmhf(std::istream& is)
{
    byte_vector data = next(is);

//     auto& htmhf = in_data.htmhf;
//     htmhf.pt = data.slice(0, 11);
//     htmhf.phi = data.slice(12, 19);
    auto& asymmetry_hthf = in_data.asymmetry_hthf[0];
    asymmetry_hthf.count = data.slice(20, 27);
    auto& centrality = in_data.centrality;
    for (size_t i = 0; i < 4; ++i)
    {
        centrality[i+4] = data.slice(28+i, 28+i);
    }

    if (verbose)
    {
        std::cerr << asymmetry_hthf << EOL;
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

void test_vector::load_externals(std::istream& is)
{
    externals = next(is);
    assert(externals.data.size() == (external_size / byte_vector::byte_bits));
    if (verbose)
        std::cerr << "<externals=0x" << externals << ">" << EOL;
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
