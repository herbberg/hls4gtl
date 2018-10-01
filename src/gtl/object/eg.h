#ifndef gtl_object_eg_h
#define gtl_object_eg_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct eg
{
    typedef ap_uint<9> pt_type;
    typedef ap_int<8> eta_type;
    typedef ap_uint<8> phi_type;
    typedef ap_uint<2> iso_type;

    pt_type pt;
    eta_type eta;
    phi_type phi;
    iso_type iso;
};

} // namespace object
} // namespace gtl

#endif
