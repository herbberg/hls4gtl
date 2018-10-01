#ifndef gtl_utils_signal_vector_h
#define gtl_utils_signal_vector_h

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace utils {

// Generic signal type vector
template<size_t N>
struct signal_vector
{
    typedef size_t size_type;
    typedef ap_uint<N> value_type;
    typedef ap_uint<1> signal_type;

    static const size_type size = N;

    value_type value;

    signal_type operator[](size_t pos) const
    {
        const value_type mask = (0x1 << pos);
        return value & mask;
    }
};

} // namespace utils
} // namespace gtl

#endif
