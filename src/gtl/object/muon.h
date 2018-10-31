#ifndef gtl_object_muon_h
#define gtl_object_muon_h

#include <ap_int.h>
#include "../../definitions.h"

namespace gtl {
namespace object {

struct muon
{
    typedef ap_uint<10> phi_type;
    typedef ap_uint<9> pt_type;
    typedef ap_uint<4> quality_type;
    typedef ap_int<9> eta_type;
    typedef ap_uint<2> iso_type;
    typedef ap_uint<2> charge_type;

    phi_type phi;
    pt_type pt;
    quality_type qual;
    eta_type eta;
    iso_type iso;
    charge_type charge;
};

} // namespace object
} // namespace gtl

#endif
