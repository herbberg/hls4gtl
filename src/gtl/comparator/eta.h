#ifndef gtl_comparator_eta_h
#define gtl_comparator_eta_h

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace comparator {

template<typename T1, typename T2>
ap_uint<1> eta(const T1& cut, const T2& object)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> result = false;

    // Result is true if no windows are defined
    if (cut.n_eta == 0)
    {
        result = true;
    }
    else
    {
        for (size_t i = 0; i < T1::ETA_WINDOWS; ++i)
        {
#pragma HLS ARRAY_PARTITION variable=cut.eta complete dim=0
#pragma HLS UNROLL
            if (i < cut.n_eta)
            {
                result |= (object.eta >= cut.eta[i].minimum) and (object.eta <= cut.eta[i].maximum);
            }
        }
    }
    return result;
}

} // namespace comparator
} // namespace gtl

#endif
