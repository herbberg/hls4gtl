#ifndef gtl_cut_asymmetry_ethf_h
#define gtl_cut_asymmetry_ethf_h

#include "../object/asymmetry_ethf.h"
#include "../comparator/count.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct asymmetry_ethf
{
    typedef object::asymmetry_ethf object_type;

    object_type::count_type count;
    comparison_mode_t comparison_mode;

    ap_uint<1> comp(const object_type& object) const
    {
        return comparator::count(*this, object);        
    };
};

} // namespace cut
} // namespace gtl

#endif
