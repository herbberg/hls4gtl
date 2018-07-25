#include <stdio.h>
#include "../src/requirements.h"
#include "../src/algos.h"

#include "toolbox.h"

#include <fstream>
#include <sstream>
#include <iostream>

static const std::string TEST_VECTOR_FILE = "../../../tb/TestVector_Sample.txt";
static const std::string OUT_FILE = "algos_out.dat";

struct fake_input
{
    static const size_t object_count = MAX_OBJ;

    eg_obj_t eg_test[object_count] = {};
    jet_obj_t jet_test[object_count] = {};

    byte_vector algorithms;

    void load(const std::string& line);
    byte_vector next(std::istream& is);
};

void fake_input::load(const std::string& line)
{
    std::istringstream iss(line);

    std::cerr << "loading..." << std::endl;
    std::cerr << line << std::endl;

    size_t bx = 0;
    iss >> bx;

    const size_t MUON_COUNT = 8;
    for (size_t i = 0; i < MUON_COUNT; ++i)
    {
        byte_vector data = next(iss);
    }

    const size_t EGAMMA_COUNT = 12;
    for (size_t i = 0; i < EGAMMA_COUNT; ++i)
    {
        byte_vector data = next(iss);
        auto& eg = eg_test[i];
        eg.pt = data.slice(0, 8);
        eg.eta = data.slice(9, 16);
        std::cerr << eg << std::endl;
    }

    const size_t TAU_COUNT = 12;
    for (size_t i = 0; i < TAU_COUNT; ++i)
    {
        byte_vector data = next(iss);
    }

    const size_t JET_COUNT = 12;
    for (size_t i = 0; i < JET_COUNT; ++i)
    {
        byte_vector data = next(iss);
        auto& jet = jet_test[i];
        jet.pt = data.slice(0, 10);
        jet.eta = data.slice(11, 18);
        std::cerr << jet << std::endl;
    }

    const size_t SKIP = 13;
    for (size_t i = 0; i < SKIP; ++i)
    {
        byte_vector data = next(iss);
    }

    algorithms = next(iss);
    assert(algorithms.data.size() == 512/8);

    // Skip parsing...
}

byte_vector fake_input::next(std::istream& is)
{
    byte_vector data;
    std::string s;
    is >> s;
    data.from_hex_str(s);
    return data;
}


int main()
{
    FILE *fp;

    fake_input input;

    std::ifstream tv(TEST_VECTOR_FILE);

    std::cerr << "writing output to " << OUT_FILE << std::endl;

    fp = fopen(OUT_FILE.c_str(), "w");
    fprintf(fp, "trans  algos  eg0  eg0   eg1  eg1    eg2  jet0 jet0\n");
    fprintf(fp, "action        pt   eta   pt   eta    pt   pt    eta\n");
    fprintf(fp, "---------------------------------------------------\n");

    size_t row = 0;

    for (std::string line; std::getline(tv, line); ++row)
    {
        input.load(line);

        ap_uint<N_ALGORITHMS> output = 0;

        std::cerr << "processing..." << std::endl;

        algos(input.eg_test, input.jet_test, output);

        std::cerr << "checking..." << std::endl;

        for (size_t i = 0; i < input.algorithms.data.size(); ++i)
        {
            bool tv = input.algorithms.test(i);
            bool sim = ((output >> i) & 0x1);
            if (tv != sim)
            {
                std::cerr << ">>> mismatch [algorithm #" << i << "]: " << tv << "!=" << sim << std::endl;
            }
        }

        fprintf(fp, "   %3d  %04x  %3d  %3d   %3d  %3d    %3d   %3d  %3d\n",
            row,
            static_cast<unsigned>(output),
            static_cast<unsigned>(input.eg_test[0].pt),
            static_cast<unsigned>(input.eg_test[0].eta),
            static_cast<unsigned>(input.eg_test[1].pt),
            static_cast<unsigned>(input.eg_test[1].eta),
            static_cast<unsigned>(input.eg_test[2].pt),
            static_cast<unsigned>(input.jet_test[0].pt),
            static_cast<unsigned>(input.jet_test[0].eta)
        );
    }

    tv.close();

    fclose(fp);

}
