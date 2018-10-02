#ifndef tb_unittest_h
#define tb_unittest_h

#include "unittest_utils.h"
#include "unittest_comparator.h"

#include <cassert>

namespace unittest {

void all()
{
    utils_all();
    comparator_all();
}

} // namespace unittest

#endif
