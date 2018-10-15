#ifndef gtl_object_asymmetry_ethf_h
#define gtl_object_asymmetry_ethf_h

#include <ap_int.h>

namespace gtl {
namespace object {

  struct asymmetry_ethf
  {
      typedef ap_uint<8> count_type;

      count_type count;
  };

} // namespace object
} // namespace gtl

#endif
