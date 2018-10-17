#ifndef gtl_condition_asymmetry_h
#define gtl_condition_asymmetry_h

#include <cstdio>

namespace gtl {
namespace condition {

// Signal condition
template<typename T1, typename T2>
ap_uint<1> count(const T1& cut, const T2& data)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
    return cut.comp(data);
}

} // namespace condition
} // namespace gtl

#endif
