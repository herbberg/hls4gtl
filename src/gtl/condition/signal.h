#ifndef gtl_condition_signal_h
#define gtl_condition_signal_h

namespace gtl {
namespace condition {

// Signal condition
template<typename T1, typename T2>
ap_uint<1> signal(const T1& cut, const T2& data)
{
    return cut.comp(data);
}

} // namespace condition
} // namespace gtl

#endif
