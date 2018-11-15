#ifndef gtl_cut_charge_corr_h
#define gtl_cut_charge_corr_h

namespace gtl {
namespace cut {

struct charge_corr
{
    enum req_charge_corr_type
    {
        IGN,
        LS,
        OS
    };
    req_charge_corr_type requested_charge_correlation;
};

} // namespace cut
} // namespace gtl

#endif
