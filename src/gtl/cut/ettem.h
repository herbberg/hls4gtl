#ifndef gtl_cut_ettem_h
#define gtl_cut_ettem_h

#include "../object/ettem.h"

#include "../comparator/pt.h"

// #include "../utils/range.h"

#include <cstddef>
#include <ap_int.h>

namespace gtl {
namespace cut {

struct ettem
{
    typedef object::ettem object_type;

    object_type::pt_type pt;
    comparison_mode_t comparison_mode;

    ap_uint<1> comp(const object_type& object) const
    {
        return comparator::pt(*this, object);
    };
};

} // namespace cut
} // namespace gtl

#endif
