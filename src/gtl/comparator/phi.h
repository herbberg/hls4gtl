#ifndef gtl_comparator_phi_h
#define gtl_comparator_phi_h

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace comparator {

template<typename T1, typename T2>
ap_uint<1> phi(const T1& cut, const T2& object)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> result = false;

    // Result is true if no windows are defined
    if (cut.n_phi == 0)
    {
        result = true;
    }
    else
    {
        for (size_t i = 0; i < T1::PHI_WINDOWS; ++i)
        {
#pragma HLS ARRAY_PARTITION variable=cut.phi complete dim=0
#pragma HLS UNROLL

            if (i < cut.n_phi)
            {
                // phi less or equal maximum requirement
                ap_uint<1> phi_le_max = object.phi <= cut.phi[i].maximum;
                // phi greater or equal minimum requirement
                ap_uint<1> phi_ge_min = object.phi >= cut.phi[i].minimum;

                if (cut.phi[i].maximum >= cut.phi[i].minimum)
                {
                    // phi less or equal maximum requirement AND phi greater or equal minimum requirement, set result on true
                    result |= phi_le_max and phi_ge_min;
                }
                else
                {
                    // phi less or equal maximum requirement OR phi greater or equal minimum requirement, set result on true
                    result |= phi_le_max or phi_ge_min;
                }
            }
        }
    }
    return result;
}

} // namespace comparator
} // namespace gtl

#endif
