#ifndef ALGOS_H_
#define ALGOS_H_

#include "input.h"
#include "definitions.h"

void algos(const in_data_t in_data[N_BX_DATA], const cc_bx_comb_t charge_correlation[cc_bx_comb_type::bx_comb_size], ap_uint<1> algo[N_ALGORITHMS]);

#endif
