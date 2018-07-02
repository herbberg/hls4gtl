#include "eta_comp.h"

ap_uint<1> eta_comp (const obj_requ_t *requ, const obj_t *obj){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requ complete dim=0
#pragma HLS ARRAY_PARTITION variable=obj complete dim=0

    ap_uint<1> eta_c = 0;

		if (obj->eta <= requ->eta_w1.upper and obj->eta >= requ->eta_w1.lower and requ->n_eta >= 1) {
			eta_c = 1;
		}
		else if (obj->eta <= requ->eta_w2.upper and obj->eta >= requ->eta_w2.lower and requ->n_eta >= 2) {
			eta_c = 1;
		}
		else if (obj->eta <= requ->eta_w3.upper and obj->eta >= requ->eta_w3.lower and requ->n_eta >= 3) {
			eta_c = 1;
		}
		else if (obj->eta <= requ->eta_w4.upper and obj->eta >= requ->eta_w4.lower and requ->n_eta >= 4) {
			eta_c = 1;
		}
		else if (obj->eta <= requ->eta_w5.upper and obj->eta >= requ->eta_w5.lower and requ->n_eta >= 5) {
			eta_c = 1;
		}
		return eta_c;
}
