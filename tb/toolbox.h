#ifndef toolbox_h
#define toolbox_h

#include <sstream>
#include <string>
#include <vector>

/* Arbitrary hex string to byte vector.
 *
 * std::vector<uint8_t> v = hex2bytes("deadbeef");
 * // v = [0xbeef, 0xdead]
 *
 */
template<typename T>
std::vector<T> hex2bytes(const std::string::const_iterator& cbegin, const std::string::const_iterator& cend)
{
    static const size_t width = sizeof(T) * 2;
    const size_t size = std::distance(cbegin, cend);
    std::vector<T> v;
    v.reserve((size + width - 1) / width);
    auto crbegin = std::reverse_iterator<std::string::const_iterator>(cend);
    auto crend = std::reverse_iterator<std::string::const_iterator>(cbegin);
    for (auto it = crbegin; it < crend; it += width)
    {
        auto begin_ = std::min(crend, it + width).base();
        auto end_ = it.base();
        std::string word(begin_, end_);
        T value = std::stoul(word, 0, 16);
        v.push_back(value);
    }
    return v;
}

/* Arbitrary integer emulation (as boost multiprecision fails in HLS)
 *
 * byte_vector v;
 * v.load_hex_string("abcd");
 * uint8_t value = v.slice<uint8_t>(4, 11);
 * // value = 0xbc
 */
struct byte_vector
{
    typedef uint8_t data_type;
    typedef unsigned long long slice_type;
    static const size_t byte_bits = sizeof(data_type) * CHAR_BIT;

    std::vector<data_type> data;

    byte_vector() {}

    void from_hex_str(const std::string& s)
    {
        data = hex2bytes<data_type>(s.cbegin(), s.cend());
    }

    template<typename T = unsigned long long>
    T slice(const size_t lsb, const size_t msb) const
    {
        assert(lsb <= msb);
        const size_t width = msb - lsb + 1;
        assert(width <= sizeof(T) * byte_bits);
        T slice = 0;
        for (size_t pos = lsb; pos <= msb; ++pos)
        {
            const size_t slice_pos = pos - lsb;
            slice |= static_cast<T>(test(pos)) << slice_pos; // NOTE: required to cast bool to integer!
        }
        return slice;
    }

    bool test(const size_t pos) const
    {
        assert(pos < data.size() * byte_bits);
        const size_t word_pos = pos / byte_bits;
        const size_t bit_pos = pos % byte_bits;
        return (data.at(word_pos) >> bit_pos) & 0x1;
    }
};

std::ostream& operator<<(std::ostream& os, const byte_vector& v)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (auto it = v.data.crbegin(); it != v.data.crend(); ++it)
    {
        oss << std::setw(2) << static_cast<uint16_t>(*it);
    }
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const eg_obj_t& egamma)
{
    std::ostringstream oss;
    oss << std::hex;
    oss << "<egamma pt=" << egamma.pt << ", tau=" << egamma.eta << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const jet_obj_t& jet)
{
    std::ostringstream oss;
    oss << std::hex;
    oss << "<jet pt=" << jet.pt << ", tau=" << jet.eta << ">";
    os << oss.str();
    return os;
}

#endif
