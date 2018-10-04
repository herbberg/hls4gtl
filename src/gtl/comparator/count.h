#ifndef gtl_comparator_count_h
#define gtl_comparator_count_h

#include <ap_int.h>

namespace gtl {
namespace comparator {

template<typename T1, typename T2>
ap_uint<1> count(const T1& cut, const T2& object)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    switch(cut.comparison_mode)
    {
        case GE: return (object.count >= cut.count);
        case EQ: return (object.count == cut.count);
        case NE: return (object.count != cut.count);
    }
    return false;
}

} // namespace comparator
} // namespace gtl

#endif
