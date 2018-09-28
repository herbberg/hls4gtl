#include "ostream_utils.h"

#include <iomanip>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const tb::byte_vector& bv)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (auto it = bv.data.crbegin(); it != bv.data.crend(); ++it)
        oss << std::setw(2) << static_cast<uint16_t>(*it);
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::muon& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<muon ";
    oss << "pt=" << object.pt << ", ";
    oss << "eta=" << object.eta << ", ";
    oss << "phi=" << object.phi << ", ";
    oss << "qual=" << object.qual << ", ";
    oss << "iso=" << object.iso << ", ";
    oss << "charge=" << object.charge << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::eg& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<egamma ";
    oss << "pt=" << object.pt << ", ";
    oss << "eta=" << object.eta << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::tau& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<tau ";
    oss << "pt=" << object.pt << ", ";
    oss << "eta=" << object.eta << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::jet& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<jet ";
    oss << "pt=" << object.pt << ", ";
    oss << "eta=" << object.eta << ">";
    os << oss.str();
    return os;
}
