#ifndef gtl_cut_asymmetry_et_h
#define gtl_cut_asymmetry_et_h

#include "../object/asymmetry_et.h"
#include "../comparator/count.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct asymmetry_et
{
    typedef object::asymmetry_et object_type;

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
