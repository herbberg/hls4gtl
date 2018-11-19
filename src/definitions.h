#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <cstddef> // for size_t
#include <ap_int.h>

const size_t N_ALGORITHMS = 512;
const size_t MAX_OBJ = 12;
const size_t MAX_MUON_OBJ = 8;
const size_t MAX_REQ = 4;
const size_t N_BX_DATA = 5;

const size_t ORBIT_BX_SIZE = 3564;

enum comparison_mode_t
{
    GE,
    NE,
    EQ,
};

enum bx_data_t
{
    bx_p2,
    bx_p1,
    bx_0,
    bx_m1,
    bx_m2,
};


namespace cc_bx_comb_type{
    enum 
    {
        bx_p2_p2,
        bx_p2_p1,
        bx_p2_0,
        bx_p2_m1,
        bx_p2_m2,
        bx_p1_p1,
        bx_p1_0,
        bx_p1_m1,
        bx_p1_m2,
        bx_0_0,
        bx_0_m1,
        bx_0_m2,
        bx_m1_m1,
        bx_m1_m2,
        bx_m2_m2,
        bx_comb_size,
    };
};

// const size_t N_CC_BX_COMB = cc_bx_comb_names_t(bx_m2_m2) + 1;

typedef ap_uint<2> cc_type;

struct cc_bx_comb_t
{
    cc_type cc_double[MAX_MUON_OBJ][MAX_MUON_OBJ];
    cc_type cc_triple[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ];
    cc_type cc_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ];
};

#endif
