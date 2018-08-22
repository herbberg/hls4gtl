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

std::ostream& operator<<(std::ostream& os, const muon_obj_t& obj)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<muon ";
    oss << "pt=" << obj.pt << ", ";
    oss << "eta=" << obj.eta << ", ";
    oss << "phi=" << obj.phi << ", ";
    oss << "qual=" << obj.qual << ", ";
    oss << "iso=" << obj.iso << ", ";
    oss << "charge=" << obj.charge << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const eg_obj_t& obj)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<egamma ";
    oss << "pt=" << obj.pt << ", ";
    oss << "eta=" << obj.eta << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const tau_obj_t& obj)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<tau ";
    oss << "pt=" << obj.pt << ", ";
    oss << "eta=" << obj.eta << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const jet_obj_t& obj)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<jet ";
    oss << "pt=" << obj.pt << ", ";
    oss << "eta=" << obj.eta << ">";
    os << oss.str();
    return os;
}
