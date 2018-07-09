#include <stdio.h>
#include "../src/requirements.h"
#include "../src/algos.h"

int main () {

    const size_t ETA_SAMPLES=10;
    const size_t PT_SAMPLES=5;
    FILE *fp;

    int eg_pt_0_p,eg_eta_0_p,eg_pt_1_p,eg_eta_1_p,eg_pt_2_p;
    int jet_pt_0_p,jet_eta_0_p;
    ap_uint<n_algos>  output = 0;
    size_t row = 0;
    size_t o_p0 = 0;
    eg_obj_t eg_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
    jet_obj_t jet_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
//    obj_t eg_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
//    obj_t jet_test[12] = {(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0),(0,0,0)};
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

    fp=fopen("algos_out_4_c_cosim.dat","w");
    fprintf(fp,"[[[runtime]]]\n");
    for (size_t i=0;i<=PT_SAMPLES;i++) {
        for (size_t j=0;j<=ETA_SAMPLES;j++) {

            algos(eg_test, jet_test, output);

            o_p0 = output;
            eg_pt_0_p = eg_test[0].pt;
            eg_eta_0_p = eg_test[0].eta;
            eg_pt_1_p = eg_test[1].pt;
            eg_pt_2_p = eg_test[2].pt;
            eg_eta_1_p = eg_test[1].eta;
            jet_pt_0_p = jet_test[0].pt;
            jet_eta_0_p = jet_test[0].eta;

            fprintf(fp,"[[transaction]] %d\n", row);
            fprintf(fp,"0x0%04x\n", o_p0);
            fprintf(fp,"[[/transaction]] \n");

            eg_test[0].eta++;
            eg_test[1].eta++;
            jet_test[0].eta++;
            o_p0 = 0;
            row++;
        }
        eg_test[0].eta = -5;
        eg_test[1].eta = -4;
        jet_test[0].eta = 0;
        eg_test[0].pt = eg_test[0].pt + 5;
        eg_test[1].pt = eg_test[1].pt + 2;
        eg_test[2].pt = eg_test[2].pt + 1;
        eg_test[3].pt = eg_test[3].pt + 1;
        jet_test[0].pt++;
    }
    fprintf(fp,"[[[/runtime]]]\n");
    fclose(fp);

}
