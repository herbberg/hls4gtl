#include "../src/requirements.h"
#include "../src/algos.h"

#include <stdio.h>

int main()
{
    const size_t ETA_SAMPLES = 11;
    const size_t PT_SAMPLES = 6;

    eg_obj_t eg_test[12] = {
        {0, 0}, {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };
    jet_obj_t jet_test[12] = {
        {0, 0}, {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };

    eg_test[0].pt = 9;
    eg_test[1].pt = 8;
    eg_test[2].pt = 6;
    eg_test[3].pt = 6;
    eg_test[0].eta = -5;
    eg_test[1].eta = 0;
    eg_test[2].eta = 0;
    eg_test[3].eta = 0;
    jet_test[0].pt = 9;
    jet_test[0].eta = 0;

    // create fake test vector
    FILE *fp;
    fp = fopen("algos_out_4_c_cosim.dat", "w");
    fprintf(fp, "[[[runtime]]]\n");

    size_t row = 0;

    for (size_t i = 0; i < PT_SAMPLES; ++i)
    {
        for (size_t j = 0; j < ETA_SAMPLES; ++j)
        {
            ap_uint<n_algos> output = 0;
            algos(eg_test, jet_test, output);

            // type cast from ap_uint to size_t
            size_t value = static_cast<size_t>(output);

            // dump test vector transaction
            fprintf(fp, "[[transaction]] %d\n", row);
            fprintf(fp, "0x0%04x\n", value);
            fprintf(fp, "[[/transaction]] \n");

            eg_test[0].eta += 1;
            eg_test[1].eta += 1;
            jet_test[0].eta += 1;

            ++row;
        }
        eg_test[0].eta = -5;
        eg_test[1].eta = -4;
        jet_test[0].eta = 0;
        eg_test[0].pt += 5;
        eg_test[1].pt += 2;
        eg_test[2].pt += 1;
        eg_test[3].pt += 1;
        jet_test[0].pt += 1;
    }

    // close fake test vector
    fprintf(fp, "[[[/runtime]]]\n");
    fclose(fp);

}
