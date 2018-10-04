#ifndef gtl_object_ettem_h
#define gtl_object_ettem_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct ettem
{
    typedef ap_uint<12> pt_type;

    pt_type pt;
};

} // namespace object
} // namespace gtl

#endif
