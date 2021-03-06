#include "../src/algos.h"

#include "transaction_writer.h"

int main () {

    const size_t ETA_SAMPLES=10;
    const size_t PT_SAMPLES=5;

    int eg_pt_0_p,eg_eta_0_p,eg_pt_1_p,eg_eta_1_p,eg_pt_2_p;
    int jet_pt_0_p,jet_eta_0_p;

    ap_uint<N_ALGORITHMS> output = 0;

    eg_obj_t eg_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
    jet_obj_t jet_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
    // obj_t eg_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
    // obj_t jet_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
    eg_test[0].pt = 9;
    eg_test[1].pt = 8;
    eg_test[2].pt = 6;
    eg_test[0].eta = -5;
    eg_test[1].eta = 0;
    eg_test[2].eta = 0;
    jet_test[0].pt = 9;
    jet_test[0].eta = 0;

    // write transaction file
    tb::transaction_writer writer("algos_out_4_rtl_cosim.dat");

    // set transcation value format
    writer.set_format("0x%04x");

    for (size_t i = 0; i <= PT_SAMPLES; ++i)
    {
        for (size_t j = 0; j <= ETA_SAMPLES; ++j)
        {
            algos(eg_test, jet_test, output);

            size_t o_p0 = output;
            eg_pt_0_p = eg_test[0].pt;
            eg_eta_0_p = eg_test[0].eta;
            eg_pt_1_p = eg_test[1].pt;
            eg_pt_2_p = eg_test[2].pt;
            eg_eta_1_p = eg_test[1].eta;
            jet_pt_0_p = jet_test[0].pt;
            jet_eta_0_p = jet_test[0].eta;

            writer.append(o_p0);

            eg_test[0].eta++;
            eg_test[1].eta++;
            jet_test[0].eta++;
        }
        eg_test[0].eta = -5;
        eg_test[1].eta = -4;
        jet_test[0].eta = 0;
        eg_test[0].pt = eg_test[0].pt + 5;
        eg_test[1].pt = eg_test[1].pt + 2;
        eg_test[2].pt = eg_test[2].pt + 1;
        jet_test[0].pt++;
    }
}
