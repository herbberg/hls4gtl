#ifndef tb_hex_bytes_h
#define tb_hex_bytes_h

#include <iterator>
#include <string>
#include <vector>

namespace tb {

/* Arbitrary hex string to byte vector.
 *
 * std::vector<uint8_t> v = hex_bytes<uint8_t>("deadbeef");
 * // v = [0xbeef, 0xdead]
 *
 */
template<typename T>
std::vector<T> hex_bytes(const std::string::const_iterator& cbegin, const std::string::const_iterator& cend)
{
    static const size_t width = sizeof(T) * 2;
    const size_t size = std::distance(cbegin, cend);
    std::vector<T> v;
    v.reserve((size + width - 1) / width);
    std::reverse_iterator<std::string::const_iterator> crbegin(cend);
    std::reverse_iterator<std::string::const_iterator> crend(cbegin);
    for (auto it = crbegin; it < crend; it += width)
    {
        auto begin = std::min(crend, it + width).base();
        auto end = it.base();
        std::string word(begin, end);
        T value = std::stoul(word, 0, 16);
        v.push_back(value);
    }
    return v;
}

} //namespace tb

#endif
