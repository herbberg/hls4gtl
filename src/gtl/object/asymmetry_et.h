#ifndef gtl_object_asymmetry_et_h
#define gtl_object_asymmetry_et_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct asymmetry_et
{
    typedef ap_uint<8> count_type;

    count_type count;
};

} // namespace object
} // namespace gtl

#endif
