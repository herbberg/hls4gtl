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
    oss << "eta=" << object.eta << ", ";
    oss << "phi=" << object.phi << ", ";
    oss << "iso=" << object.iso << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::tau& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<tau ";
    oss << "pt=" << object.pt << ", ";
    oss << "eta=" << object.eta << ", ";
    oss << "phi=" << object.phi << ", ";
    oss << "iso=" << object.iso << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::jet& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<jet ";
    oss << "pt=" << object.pt << ", ";
    oss << "eta=" << object.eta << ", ";
    oss << "phi=" << object.phi << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::ett& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<ett ";
    oss << "pt=" << object.pt << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::htt& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<htt ";
    oss << "pt=" << object.pt << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::ettem& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<ettem ";
    oss << "pt=" << object.pt << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::etm& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<etm ";
    oss << "pt=" << object.pt << ", ";
    oss << "phi=" << object.phi << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::htm& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<htm ";
    oss << "pt=" << object.pt << ", ";
    oss << "phi=" << object.phi << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::etmhf& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<etmhf ";
    oss << "pt=" << object.pt << ", ";
    oss << "phi=" << object.phi << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::mbt0hfp& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<mbt0hfp ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::mbt0hfm& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<mbt0hfm ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::mbt1hfp& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<mbt1hfp ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::mbt1hfm& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<mbt1hfm ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_et& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<asymmetry_et ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_ht& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<asymmetry_ht ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_ethf& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<asymmetry_ethf ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

std::ostream& operator<<(std::ostream& os, const gtl::object::asymmetry_hthf& object)
{
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "<asymmetry_hthf ";
    oss << "count=" << object.count << ">";
    os << oss.str();
    return os;
}

