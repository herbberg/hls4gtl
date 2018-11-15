#ifndef gtl_cut_muon_h
#define gtl_cut_muon_h

#include "../object/muon.h"

#include "../comparator/pt.h"
#include "../comparator/eta.h"
#include "../comparator/phi.h"
#include "../comparator/charge.h"

#include "../utils/range.h"

#include "../../definitions.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct muon
{
    typedef object::muon object_type;
    typedef utils::range<object_type::eta_type> eta_range_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    enum req_charge_type
    {
        IGNORE,
        POSITIVE,
        NEGATIVE
    };

    enum req_charge_corr_type
    {
        LS,
        OS,
        IGN
    };

    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;
    static const size_t QUALITY_LUT_WIDTH = 16;

    ap_uint<4> slice[2];
    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    eta_range_type eta[ETA_WINDOWS];
    ap_uint<3> n_eta;
    phi_range_type phi[PHI_WINDOWS];
    ap_uint<2> n_phi;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];
    ap_uint<1> qual_lut[QUALITY_LUT_WIDTH];
    req_charge_type requested_charge;
    req_charge_corr_type requested_charge_correlation;

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_eta = comparator::eta(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        ap_uint<1> comp_qual = qual_lut[object.qual];
        ap_uint<1> comp_iso = iso_lut[object.iso];
        ap_uint<1> comp_charge = comparator::charge(*this, object);
        return comp_pt and comp_eta and comp_phi and comp_qual and comp_iso and comp_phi;
    };
};

} // namespace cut
} // namespace gtl

#endif
