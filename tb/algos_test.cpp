#include "../src/algos.h"
#include "../src/current_dist.h"

#include "test_vector.h"
#include "ostream_utils.h"

#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <iostream>

size_t run_testvector(const std::string& filename);

int main(int argc, char* argv[])
{
    // Dump menu information
    std::cerr << "> menu name: " << IMPL_MENU_NAME << std::endl;
    std::cerr << "> menu UUID: " << IMPL_MENU_UUID << std::endl;
    std::cerr << "> dist UUID: " << IMPL_DIST_UUID << std::endl;

    // Collect command line arguments
    std::vector<std::string> args(argv, argv + argc);

    // Warning if no test vectors are supplied
    if (args.size() < 2)
    {
        std::cerr << "[WARNING] no test vectors supplied!" << std::endl;
        return EXIT_SUCCESS;
    }

    std::map<std::string, size_t> results;
    size_t failed = 0;

    for (size_t i = 1; i < args.size(); ++i)
    {
        const std::string& filename = args.at(i);
        size_t result = run_testvector(filename);
        results[filename] = result;
        if (result)
        {
            ++failed;
        }
    }

    for (std::map<std::string, size_t>::iterator it = results.begin(); it != results.end(); ++it)
    {
        const std::string state = it->second == 0 ? "SUCCESS" : "FAILED";
        std::cerr << it->first << ": " << state << std::endl;
    }

    // Xilinx UG902, page 200: good test benches should return exit codes!

    if (failed)
    {
        std::cerr << "*** " << failed << " tests failed in total." << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "> perfect match!" << std::endl;
    return EXIT_SUCCESS;
}

size_t run_testvector(const std::string& filename)
{
    tb::test_vector input;
    input.verbose = false;

    // open test vector file, sef optional file using argv[1]
    std::ifstream tv(filename);
    if (not tv.is_open())
    {
        std::cerr << "*** unable to read test vector from: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "> reading test vector from: " << filename << std::endl;

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

    return mismatches;
}
