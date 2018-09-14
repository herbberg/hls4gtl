#ifndef tb_byte_vector_h
#define tb_byte_vector_h

#include "bytelify.h"

#include <cassert>
#include <climits>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace tb {

/* Arbitrary integer emulation (as boost multi-precision fails in HLS)
 *
 * byte_vector v;
 * v.from_hex_str("abcd");
 * uint8_t value = v.slice<uint8_t>(4, 11);
 * // value = 0xbc
 */
struct byte_vector
{
    typedef uint8_t data_type;
    typedef unsigned long long slice_type;
    static const size_t byte_bits = sizeof(data_type) * CHAR_BIT;

    std::vector<data_type> data;

    byte_vector() = default;
    byte_vector(const std::string& s)
    {
      from_hex_str(s);
    }
    virtual ~byte_vector() = default;

    /* Read byte vector from hex string. */
    void from_hex_str(const std::string& s)
    {
        data = bytelify<data_type>(s.cbegin(), s.cend());
    }

    /* Extract bit slice from byte vector. */
    template<typename T = unsigned long long>
    T slice(const size_t lsb, const size_t msb) const
    {
        assert(lsb <= msb);
        const size_t width = msb - lsb + 1;
        assert(width <= sizeof(T) * byte_bits);
        T slice = 0;
        // collect slice bits
        // TODO: increase performance
        for (size_t pos = lsb; pos <= msb; ++pos)
        {
            const size_t slice_pos = pos - lsb;
            slice |= static_cast<T>(test(pos)) << slice_pos; // NOTE: required to cast bool to integer!
        }
        return slice;
    }

    /* Test value of bit at a give position. */
    bool test(const size_t pos) const
    {
        assert(pos < data.size() * byte_bits);
        const size_t word_pos = pos / byte_bits;
        const size_t bit_pos = pos % byte_bits;
        return (data.at(word_pos) >> bit_pos) & 0x1;
    }

    /* Return size in bytes. */
    size_t size() const
    {
        return data.size();
    }

    /* Return size in bits. */
    size_t size_bits() const
    {
        return size() * byte_bits;
    }
};

} //namespace tb

#endif
