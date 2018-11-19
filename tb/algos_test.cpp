
#include "../src/algos.h"
#include "../src/current_dist.h"
#include "charge_correlation.h"

#include "test_vector.h"
#include "ostream_utils.h"
#include "unittest.h"

#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <iostream>

size_t run_testvector(const std::string& filename);

int main(int argc, char* argv[])
{
    // Run unittests
    std::cerr << "INFO: running unit tests..." << std::endl;
    unittest::all();

    // Dump menu information
    std::cerr << "INFO: menu name: " << IMPL_MENU_NAME << std::endl;
    std::cerr << "INFO: menu UUID: " << IMPL_MENU_UUID << std::endl;
    std::cerr << "INFO: dist UUID: " << IMPL_DIST_UUID << std::endl;

    // Collect command line arguments
    std::vector<std::string> args(argv, argv + argc);

    // Warning if no test vectors are supplied
    if (args.size() < 2)
    {
        std::cerr << "WARNING: no test vectors supplied!" << std::endl;
        return EXIT_SUCCESS;
    }

    // Record results for every test vector
    std::map<std::string, size_t> results;
    size_t failed = 0;

    // Process testvectors
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

    std::cerr << "INFO: summary:" << std::endl;
    for (std::map<std::string, size_t>::iterator it = results.begin(); it != results.end(); ++it)
    {
        const std::string state = it->second == 0 ? "SUCCESS" : "FAILED";
        std::cerr << "INFO: " << it->first << ": " << state << std::endl;
    }

    // Xilinx UG902, page 200: good test benches should return exit codes!

    if (failed)
    {
        std::cerr << "ERROR: *** " << failed << " tests failed in total." << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "INFO: passed test, perfect match!" << std::endl;
    return EXIT_SUCCESS;
}

size_t run_testvector(const std::string& filename)
{
    tb::test_vector input;
    input.verbose = false;

    in_data_t in_data_bx[N_BX_DATA] = {};
    ap_uint<2> muon_charge[N_BX_DATA][N_BX_DATA][MAX_MUON_OBJ];
    cc_bx_comb_t charge_correlation[cc_bx_comb_type::bx_comb_size] = {};

    // open test vector file, sef optional file using argv[1]
    std::ifstream tv(filename);
    if (not tv.is_open())
    {
        std::cerr << "ERROR: *** unable to read test vector from: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "INFO: processing testvector '" << filename << "'" << std::endl;

    size_t row = 0;
    size_t mismatches = 0;    
    
    for (std::string line; std::getline(tv, line); ++row)
    {
// need to be extended for 5 bx 
        input.load(line);
        in_data_bx[bx_0] = input.in_data;
        for (size_t k = 0; k < MAX_MUON_OBJ; ++k)
        {
            muon_charge[bx_0][bx_0][k] = input.in_data.muon[k].charge;
        }
        tb::charge_correlation_logic(muon_charge[bx_0][bx_0], charge_correlation[cc_bx_comb_type::bx_0_0]);
        
        ap_uint<1> output[N_ALGORITHMS] = {};

        if (input.verbose)
            std::cerr << "INFO: processing event " << input.bx << " ..." << std::endl;

        algos(in_data_bx, charge_correlation, output);

        if (input.verbose)
            std::cerr << "INFO: checking event " << input.bx << " ..." << std::endl;
        
        size_t event_mismatches = 0;

        for (size_t i = 0; i < N_ALGORITHMS; ++i)
        {
            const bool algorithm_tv = input.algorithms.test(i);
            const bool algorithm_sim = output[i];
            if (algorithm_tv != algorithm_sim)
            {
                ++event_mismatches;
                std::cerr << "ERROR: *** mismatch> [event=" << input.bx << "] [algorithm=" << i << "]: ";
                std::cerr << algorithm_tv << "!=" << algorithm_sim << " (tv/sim)\n";
            }
        }

        mismatches += event_mismatches;

        if (event_mismatches)
        {
            std::cerr << "ERROR: *** " << event_mismatches << " mismatch(es) in event " << input.bx << "." << std::endl;
        }
        else
        {
            if (input.verbose)
                std::cerr << "INFO: success." << std::endl;
        }
    }

    tv.close();

    if (mismatches)
        std::cerr << "ERROR: " << mismatches << "mismatches." << std::endl;
    else
        std::cerr << "INFO: success." << std::endl;

    return mismatches;
}
