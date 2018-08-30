/*
 * auto generated menu implementation
 */

#ifndef impl_logic_h
#define impl_logic_h

#include "../../src/definitions.h"
#include "../../src/templates.h"
#include "../../src/obj.h"

#include "../../impl/hls/conditions.h"

#include <ap_int.h>

namespace impl {

struct logic
{
    void process(const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], ap_uint<N_ALGORITHMS>& algo) const
    {
#pragma HLS INTERFACE ap_none port=eg
#pragma HLS INTERFACE ap_none port=jet
#pragma HLS INTERFACE ap_none port=algos
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1

        {{ conditions }}

        algo = 0;
        {{ seeds }}
    }
};

} // namespace impl

#endif
