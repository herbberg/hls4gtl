#include "algos.h"

#include "../impl/hls/logic.h"

void algos (const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], ap_uint<N_ALGORITHMS>& algo)
{
#pragma HLS INTERFACE ap_none port=eg
#pragma HLS INTERFACE ap_none port=jet
#pragma HLS INTERFACE ap_none port=algos
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1

    static ::impl::logic logic = {};
    logic.process(eg, jet, algo);
}
