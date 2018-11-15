#ifndef gtl_cut_jet_h
#define gtl_cut_jet_h

#include "../object/jet.h"

#include "../comparator/pt.h"
#include "../comparator/eta.h"
#include "../comparator/phi.h"

#include "../utils/range.h"

#include "../../definitions.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct jet
{
    typedef object::jet object_type;
    typedef utils::range<object_type::eta_type> eta_range_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;

    ap_uint<4> slice[2];
    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    eta_range_type eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    phi_range_type phi[PHI_WINDOWS];
    ap_int<2> n_phi;

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_eta = comparator::eta(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        return comp_pt and comp_eta and comp_phi;
    };
};

} // namespace cut
} // namespace gtl

#endif
