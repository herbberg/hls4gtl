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
    // Width in nibbles depending on type T
    static const size_t width = sizeof(T) * 2;
    // Calulate size of input string
    const size_t size = std::distance(cbegin, cend);
    std::vector<T> v;
    // Reserve required number of Ts
    v.reserve((size + width - 1) / width);
    // Reverse iterators to traverse string from right to left
    std::reverse_iterator<std::string::const_iterator> crbegin(cend);
    std::reverse_iterator<std::string::const_iterator> crend(cbegin);
    // Traverse input string in slices of type T
    for (auto it = crbegin; it < crend; it += width)
    {
        // Iterators for slice (dereived from reverse iterators)
        auto begin = std::min(crend, it + width).base();
        auto end = it.base();
        // Convert string to T
        std::string word(begin, end);
        T value = std::stoul(word, 0, 16);
        v.push_back(value);
    }
    return v;
}

} //namespace tb

#endif
