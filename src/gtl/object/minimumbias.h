#ifndef gtl_object_minimumbias_h
#define gtl_object_minimumbias_h

#include <ap_int.h>

namespace gtl {
namespace object {

  struct minimumbias
  {
      typedef ap_uint<4> count_type;

      count_type count;
  };

} // namespace object
} // namespace gtl

#endif
