#include "../src/algos.h"
#include "../src/current_dist.h"

#include "transaction_writer.h"

int main()
{
    const size_t ETA_SAMPLES = 11;
    const size_t PT_SAMPLES = 6;

    in_data_t in_data_test = {
        {
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0}            
        },
        {
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0}            
        },
        {
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0}            
        },
        {
            {0, 0}, {0, 0}, {0, 0}, {0, 0},
            {0, 0}, {0, 0}, {0, 0}, {0, 0}
        },
        {}, {}, {}, {}, {}, {}
    };

//     eg_obj_t in_data.eg[12] = {
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0}
//     };
//     jet_obj_t in_data.jet[12] = {
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0}
//     };
// 
//     tau_obj_t in_data.tau[12] = {
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0}
//     };
// 
//     muon_obj_t in_data.muon[8] = {
//         {0, 0}, {0, 0}, {0, 0}, {0, 0},
//         {0, 0}, {0, 0}, {0, 0}, {0, 0}
//     };
// 
//     asym_t asymet_test = {};
//     asym_t asymht_test = {};
//     asym_t asymethf_test = {};
//     asym_t asymhthf_test = {};
//     asym_t centrality_test = {};
//     asym_t extcond_test = {};

    in_data_test.eg[0].pt = 9;
    in_data_test.eg[1].pt = 8;
    in_data_test.eg[2].pt = 6;
    in_data_test.eg[3].pt = 6;
    in_data_test.eg[0].eta = 0x8D;
    in_data_test.eg[1].eta = 0;
    in_data_test.eg[2].eta = 0;
    in_data_test.eg[3].eta = 0;
    in_data_test.jet[0].pt = 9;
    in_data_test.jet[0].eta = 0;

    // Dump menu information
    std::cerr << "INFO: menu name: " << IMPL_MENU_NAME << std::endl;
    std::cerr << "INFO: menu UUID: " << IMPL_MENU_UUID << std::endl;
    std::cerr << "INFO: dist UUID: " << IMPL_DIST_UUID << std::endl;

    // create fake test vector
    tb::transaction_writer writer("algos_out_4_c_cosim.dat");

    // set transcation value format
    writer.set_format("0x0%04x");

    for (size_t i = 0; i < PT_SAMPLES; ++i)
    {
        for (size_t j = 0; j < ETA_SAMPLES; ++j)
        {
            ap_uint<1> output[N_ALGORITHMS] = {};
            algos(in_data_test, output);

            // type cast from ap_uint to size_t
//            size_t value = static_cast<size_t>(output);

            // dump test vector transaction
//            writer.append(value);

            in_data_test.eg[0].eta += 0x16;
            in_data_test.eg[1].eta += 0x16;
            in_data_test.jet[0].eta += 0x16;
        }
        in_data_test.eg[0].eta = 0x8D;
        in_data_test.eg[1].eta = 0xA4;
        in_data_test.jet[0].eta = 0;
        in_data_test.eg[0].pt += 5;
        in_data_test.eg[1].pt += 2;
        in_data_test.eg[2].pt += 1;
        in_data_test.eg[3].pt += 1;
        in_data_test.jet[0].pt += 1;
    }
}
