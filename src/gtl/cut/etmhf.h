#ifndef gtl_cut_etmhf_h
#define gtl_cut_etmhf_h

#include "../object/etmhfhf.h"

#include "../comparator/pt.h"
#include "../comparator/phi.h"

// #include "../utils/range.h"

#include "../../definitions.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct etmhfhf
{
    typedef object::etmhf object_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    static const size_t PHI_WINDOWS = 2;

    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    phi_range_type phi[PHI_WINDOWS];
    ap_int<2> n_phi;

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        return comp_pt and comp_phi;
    };
};

} // namespace cut
} // namespace gtl

#endif
