#ifndef gtl_comparator_charge_h
#define gtl_comparator_charge_h

#include <ap_int.h>

namespace gtl {
namespace comparator {

template<typename T1, typename T2>
ap_uint<1> charge(const T1& cut, const T2& object)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    switch(cut.requested_charge)
    {
        case T1::IGNORE: return true;
        case T1::POSITIVE: return (object.charge == 2); // 0b10
        case T1::NEGATIVE: return (object.charge == 3); // 0b11
    }
    return false;
}

} // namespace comparator
} // namespace gtl

#endif
