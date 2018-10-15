#ifndef gtl_object_asymmetry_ht_h
#define gtl_object_asymmetry_ht_h

#include <ap_int.h>

namespace gtl {
namespace object {

  struct asymmetry_ht
  {
      typedef ap_uint<8> count_type;

      count_type count;
  };

} // namespace object
} // namespace gtl

#endif
