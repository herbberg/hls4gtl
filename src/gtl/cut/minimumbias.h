#ifndef gtl_cut_minimumbias_h
#define gtl_cut_minimumbias_h

#include "../object/minimumbias.h"
#include "../comparator/count.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct minimumbias
{
    typedef object::minimumbias object_type;

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
