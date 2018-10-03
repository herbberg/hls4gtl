#ifndef gtl_object_etmhf_h
#define gtl_object_etmhf_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct etmhf
{
    typedef ap_uint<12> pt_type;
    typedef ap_uint<8> phi_type;

    pt_type pt;
    phi_type phi;
};

} // namespace object
} // namespace gtl

#endif
