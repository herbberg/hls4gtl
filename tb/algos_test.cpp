#include "../src/requirements.h"
#include "../src/algos.h"

#include "test_vector.h"
#include "ostream_utils.h"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>

static const std::string TEST_VECTOR_FILE = "../../../tb/TestVector_Sample.txt";
static const std::string OUT_FILE = "algos_out.dat";

class Logger
{
protected:
    FILE* fp = nullptr;
public:
    Logger(const std::string& filename)
    {
        fp = fopen(filename.c_str(), "w");
    }
    virtual ~Logger()
    {
        fclose(fp);
    }
    void log_header()
    {
        fprintf(fp, "trans  algos  eg0  eg0   eg1  eg1    eg2  jet0 jet0\n");
        fprintf(fp, "action        pt   eta   pt   eta    pt   pt    eta\n");
        fprintf(fp, "---------------------------------------------------\n");
    }
    void log_footer()
    {
        fprintf(fp, "---------------------------------------------------\n");
    }
    void log_sample(size_t row, const tb::test_vector& input, const ap_uint<N_ALGORITHMS>& output)
    {
        fprintf(fp, "   %3d  %04x  %3d  %3d   %3d  %3d    %3d   %3d  %3d\n",
            row,
            static_cast<unsigned>(output),
            static_cast<unsigned>(input.egamma_obj[0].pt),
            static_cast<unsigned>(input.egamma_obj[0].eta),
            static_cast<unsigned>(input.egamma_obj[1].pt),
            static_cast<unsigned>(input.egamma_obj[1].eta),
            static_cast<unsigned>(input.egamma_obj[2].pt),
            static_cast<unsigned>(input.jet_obj[0].pt),
            static_cast<unsigned>(input.jet_obj[0].eta)
        );
    }
};

int main()
{
    tb::test_vector input;

    // open test vector file
    std::ifstream tv(TEST_VECTOR_FILE);

    std::cerr << "writing output to " << OUT_FILE << std::endl;

    Logger logger(OUT_FILE);
    logger.log_header();

    size_t row = 0;

    for (std::string line; std::getline(tv, line); ++row)
    {
        input.load(line);

        ap_uint<N_ALGORITHMS> output = 0;

        std::cerr << "processing..." << std::endl;

        algos(input.egamma_obj, input.jet_obj, output);

        std::cerr << "checking..." << std::endl;

        for (size_t i = 0; i < input.algorithms.size_bits(); ++i)
        {
            bool atv = input.algorithms.test(i);
            bool asim = ((output >> i) & 0x1);
            if (atv != asim)
            {
                std::cerr << ">>> mismatch [algorithm #" << i << "]: ";
                std::cerr << atv << "!=" << asim << " (tv/sim)\n";
            }
        }

        logger.log_sample(row, input, output);
    }

    tv.close();
}
