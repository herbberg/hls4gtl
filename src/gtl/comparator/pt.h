#ifndef gtl_comparator_pt_h
#define gtl_comparator_pt_h

#include <ap_int.h>

namespace gtl {
namespace comparator {

template<typename T1, typename T2>
ap_uint<1> pt(const T1& cut, const T2& object)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    switch(cut.comparison_mode)
    {
        case GE: return (object.pt >= cut.pt);
        case EQ: return (object.pt == cut.pt);
        case NE: return (object.pt != cut.pt);
    }
    return false;
}

} // namespace comparator
} // namespace gtl

#endif
