#ifndef gtl_cut_external_h
#define gtl_cut_external_h

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

// External signal cut
struct external
{
    typedef size_t channel_id_type;
    typedef ap_uint<1> result_type;

    channel_id_type channel_id;

    template<typename T>
    ap_uint<1> comp(const T& external) const
    {
        return external[channel_id];
    };
};

} // namespace cut
} // namespace gtl

#endif
