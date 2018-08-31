#include "algos.h"

#include "definitions.h"
#include "obj.h"

#include "current_dist.h"

void algos (const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], ap_uint<N_ALGORITHMS>& algo)
{
#pragma HLS INTERFACE ap_none port=eg
#pragma HLS INTERFACE ap_none port=jet
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS INTERFACE ap_ctrl_none port=return

    // create static logic
    static ::impl::conditions::logic conditions_logic = {};
    static ::impl::seeds::logic seeds_logic = {};

    // TODO: use as output
    ::impl::seeds::logic::signal_type seeds[N_ALGORITHMS];
#pragma HLS ARRAY_PARTITION variable=seeds complete dim=1

    // update condition states
    conditions_logic.process(eg, jet);

    // update seed states
    seeds_logic.process(conditions_logic);

    // map seed states to output
    seeds_logic.map(seeds);

    // TODO: replace by array
    algo = 0;
    for (size_t i = 0; i < N_ALGORITHMS; ++i)
    {
#pragma HLS UNROLL
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(seeds[i]) << i;
    }
}
