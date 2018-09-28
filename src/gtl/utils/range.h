#ifndef gtl_utils_range_h
#define gtl_utils_range_h

namespace gtl {
namespace utils {

template<typename T>
struct range
{
    typedef T value_type;

    value_type minimum;
    value_type maximum;
};

} // namespace utils
} // namespace gtl

#endif
