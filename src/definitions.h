#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <cstddef> // for size_t

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

#endif
