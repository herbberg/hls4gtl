#ifndef gtl_cut_signal_h
#define gtl_cut_signal_h

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

// Signal cut (used for external signals and for centrality "signals")
struct signal
{

    typedef size_t signal_id_type;
    signal_id_type signal_id;

};

} // namespace cut
} // namespace gtl

#endif
