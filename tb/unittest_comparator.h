#ifndef tb_unittest_comparator_h
#define tb_unittest_comparator_h

#include "../src/gtl/comparator.h"
#include "../src/gtl/object.h"
#include "../src/gtl/cut.h"

#include <cassert>

namespace unittest {

void comparator_pt()
{
    using namespace gtl;

    cut::jet cut = {};
    object::jet object = {};

    assert(cut.comparison_mode == GE); // test default
    cut.pt = 0x42;
    object.pt = 0x42; // equal threshold
    assert(comparator::pt(cut, object) == true);
    cut.pt = 0x31; // reduce threshold
    assert(comparator::pt(cut, object) == true);
    cut.pt = 0x55; // increase threshold
    assert(comparator::pt(cut, object) == false);

    cut.comparison_mode = EQ;
    cut.pt = 0x42;
    object.pt = 0x42; // equal
    assert(comparator::pt(cut, object) == true);
    object.pt = 0x41; // not equal, lower
    assert(comparator::pt(cut, object) == false);
    object.pt = 0x43; // not equal, higher
    assert(comparator::pt(cut, object) == false);

    cut.comparison_mode = NE;
    cut.pt = 0x42;
    object.pt = 0x42; // equal
    assert(comparator::pt(cut, object) == false);
    object.pt = 0x41; // not equal, lower
    assert(comparator::pt(cut, object) == true);
    object.pt = 0x43; // not equal, higher
    assert(comparator::pt(cut, object) == true);
}

void comparator_all()
{
    comparator_pt();
}

} // namespace unittest

#endif
