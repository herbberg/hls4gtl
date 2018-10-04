#ifndef gtl_object_htt_h
#define gtl_object_htt_h

#include <ap_int.h>

namespace gtl {
namespace object {

struct htt
{
    typedef ap_uint<12> pt_type;

    pt_type pt;
};

} // namespace object
} // namespace gtl

#endif
