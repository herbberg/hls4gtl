#ifndef gtl_cut_mbt0hfm_h
#define gtl_cut_mbt0hfm_h

#include "../object/mbt0hfm.h"
#include "../comparator/count.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct mbt0hfm
{
    typedef object::mbt0hfm object_type;

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
