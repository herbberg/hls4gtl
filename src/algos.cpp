#include "algos.h"

#include "definitions.h"
#include "obj.h"

#include "current_dist.h"

void algos (const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], ap_uint<N_ALGORITHMS>& algo)
{
#pragma HLS INTERFACE ap_none port=eg
#pragma HLS INTERFACE ap_none port=jet
#pragma HLS INTERFACE ap_none port=algos
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1

    ::impl::logic logic = {};

    ::impl::logic::signal_type seeds[N_ALGORITHMS];
#pragma HLS ARRAY_PARTITION variable=seeds complete dim=1

    logic.process(eg, jet, seeds);

    algo = 0;
    for (size_t i = 0; i < N_ALGORITHMS; ++i)
    {
#pragma HLS UNROLL
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(seeds[i]) << i;
    }
}
