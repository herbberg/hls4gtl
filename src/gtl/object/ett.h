#ifndef gtl_object_ett_h
#define gtl_object_ett_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct ett
{
    typedef ap_uint<12> pt_type;

    pt_type pt;
};

} // namespace object
} // namespace gtl

#endif
