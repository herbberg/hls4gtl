#ifndef gtl_object_jet_h
#define gtl_object_jet_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct jet
{
    typedef ap_uint<11> pt_type;
    typedef ap_int<8> eta_type;
    typedef ap_uint<8> phi_type;

    pt_type pt;
    eta_type eta;
    phi_type phi;
};

} // namespace object
} // namespace gtl

#endif
