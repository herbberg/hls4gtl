#include "eta_comp.h"

ap_uint<1> eta_comp (const obj_requ_t requ, const obj_t obj){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requ complete dim=0
#pragma HLS ARRAY_PARTITION variable=obj complete dim=0

	ap_uint<1> eta_c = 0;

	for (size_t i = 0; i < requ.n_eta; i++) {
#pragma HLS unroll
		if (obj.eta <= requ.eta[i].upper and obj.eta >= requ.eta[i].lower) {
			eta_c = 1;
		}
	}
	return eta_c;
}
