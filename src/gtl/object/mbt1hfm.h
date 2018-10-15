#ifndef gtl_object_mbt1hfm_h
#define gtl_object_mbt1hfm_h

#include <ap_int.h>

namespace gtl {
namespace object {

  struct mbt1hfm
  {
      typedef ap_uint<4> count_type;

      count_type count;
  };

} // namespace object
} // namespace gtl

#endif
