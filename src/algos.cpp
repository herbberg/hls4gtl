#include "algos.h"

#include "definitions.h"
#include "input.h"

#include "current_dist.h"

void algos(const in_data_t in_data[N_BX_DATA], const cc_bx_comb_t charge_correlation[cc_bx_comb_type::bx_comb_size], ap_uint<1> algo[N_ALGORITHMS])
{
#pragma HLS INTERFACE ap_none port=in_data
#pragma HLS INTERFACE ap_none port=charge_correlation
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS INTERFACE ap_ctrl_none port=return

    // create static logic
    static ::impl::conditions::logic conditions_logic = {};
    static ::impl::seeds::logic seeds_logic = {};

    // update condition states
    conditions_logic.process(in_data, charge_correlation);

    // update seed states
    seeds_logic.process(conditions_logic);

    for (size_t i = 0; i <N_ALGORITHMS; i++)
    {
#pragma HLS UNROLL
        algo[i] = 0;
    }

    // map seed states to output
    seeds_logic.map(algo);

}
