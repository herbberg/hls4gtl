#include "algos.h"

#include "definitions.h"
#include "input.h"

#include "current_dist.h"

void algos(const in_data_t& in_data, ap_uint<1> algo[N_ALGORITHMS])
{
#pragma HLS INTERFACE ap_none port=in_data
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS INTERFACE ap_ctrl_none port=return

    // create static logic
    static ::impl::conditions::logic conditions_logic = {};
    static ::impl::seeds::logic seeds_logic = {};

    // update condition states
    conditions_logic.process(in_data);

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
