/*
 * auto generated menu implementation
 */

#ifndef impl_logic_h
#define impl_logic_h

#include "../src/definitions.h"
#include "../src/templates.h"
#include "../src/obj.h"

#include "../impl/const.h"

#include <ap_int.h>

namespace impl {

struct logic
{
    template<typename DIN1, typename DIN2, typename DOUT>
    void process(const DIN1& eg, const DIN2& jet, DOUT& algo) const
    {
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1

        {{ conditions }}

        algo = 0;
        {{ algorithms }}
    }
};

} // namespace impl

#endif
