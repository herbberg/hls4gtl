#ifndef gtl_cut_centrality_h
#define gtl_cut_centrality_h

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

// Centrality signal cut
struct centrality
{
    typedef size_t signal_id_type;
    typedef ap_uint<1> result_type;

    signal_id_type signal_id;

    template<typename T>
    result_type comp(const T& centrality) const
    {
        return centrality[signal_id];
    };
};

} // namespace cut
} // namespace gtl

#endif
