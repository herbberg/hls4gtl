#ifndef gtl_object_muon_h
#define gtl_object_muon_h

#include <ap_int.h>
#include "../../definitions.h"

namespace gtl {
namespace object {

struct muon
{
    typedef ap_uint<10> phi_type;
    typedef ap_uint<9> pt_type;
    typedef ap_uint<4> quality_type;
    typedef ap_int<9> eta_type;
    typedef ap_uint<2> iso_type;
    typedef ap_uint<2> charge_type;

    phi_type phi;
    pt_type pt;
    quality_type qual;
    eta_type eta;
    iso_type iso;
    charge_type charge;
};

struct charge_correlation
{
    ap_uint<1> ls_double[MAX_MUON_OBJ][MAX_MUON_OBJ];
    ap_uint<1> os_double[MAX_MUON_OBJ][MAX_MUON_OBJ];
    ap_uint<1> ls_triple[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ];
    ap_uint<1> os_triple[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ];
    ap_uint<1> ls_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ];
    ap_uint<1> os_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ];
    
//     struct value
//     {
// //        const ap_uint<2> LS = 0;
// //        const ap_uint<2> OS = 1;
// //        const ap_uint<2> IGN = 2;
//        const size_t LS = 0;
//        const size_t OS = 1;
//        const size_t IGN = 2;
//     };
};

} // namespace object
} // namespace gtl

#endif
