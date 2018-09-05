#include "../src/algos.h"
#include "../src/current_dist.h"

#include "test_vector.h"
#include "ostream_utils.h"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>

static const std::string TEST_VECTOR_FILE = "../../../tb/TestVector_Sample.txt";
static const std::string OUT_FILE = "algos_out.dat";

int main(int argc, char* argv[])
{
    std::vector<std::string> args(argv, argv + argc);

    // Dump menu information
    std::cerr << "> menu name: " << IMPL_MENU_NAME << std::endl;
    std::cerr << "> menu UUID: " << IMPL_MENU_UUID << std::endl;
    std::cerr << "> dist UUID: " << IMPL_DIST_UUID << std::endl;

    tb::test_vector input;
    input.verbose = false;

    // open test vector file, sef optional file using argv[1]
    std::ifstream tv(args.size() > 1 ? args.at(1) : TEST_VECTOR_FILE);

    std::cerr << "> writing output to: " << OUT_FILE << std::endl;

    size_t row = 0;
    size_t mismatches = 0;

    for (std::string line; std::getline(tv, line); ++row)
    {
        input.load(line);

        ap_uint<1> output[N_ALGORITHMS] = {};

        if (input.verbose)
            std::cerr << "> processing event " << input.bx << " ..." << std::endl;

        algos(input.egamma_obj, input.jet_obj, output);

        if (input.verbose)
            std::cerr << "> checking event " << input.bx << " ..." << std::endl;

        size_t event_mismatches = 0;

        for (size_t i = 0; i < N_ALGORITHMS; ++i)
        {
            const bool algorithm_tv = input.algorithms.test(i);
            const bool algorithm_sim = output[i];
            if (algorithm_tv != algorithm_sim)
            {
                ++event_mismatches;
                std::cerr << "*** mismatch> [event=" << input.bx << "] [algorithm=" << i << "]: ";
                std::cerr << algorithm_tv << "!=" << algorithm_sim << " (tv/sim)\n";
            }
        }

        mismatches += event_mismatches;

        if (event_mismatches)
        {
            std::cerr << "*** " << event_mismatches << " mismatch(es) in event " << input.bx << "." << std::endl;
        }
        else
        {
            if (input.verbose)
                std::cerr << "> success." << std::endl;
        }
    }

    tv.close();

    // Xilinx UG902, page 200: good test benches should return exit codes!

    if (mismatches)
    {
        std::cerr << "*** " << mismatches << " total mismatch(es)" << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "> perfect match!" << std::endl;
    return EXIT_SUCCESS;
}
