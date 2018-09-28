#include "eta_comp.h"

ap_uint<1> eta_comp (const obj_requ_t requ, const obj_t obj){

#pragma HLS INTERFACE ap_ctrl_none port=return

	ap_uint<1> eta_c = 0;

	if (requ.n_eta == 0) {
		eta_c = 1;
	}
	else
	{
		for (size_t i = 0; i < ETA_WINDOWS; i++)
		{
#pragma HLS unroll
			if (obj.eta <= requ.eta[i].maximum and obj.eta >= requ.eta[i].minimum and i <= requ.n_eta-1) {
			eta_c = 1;
			}
		}
	}
	return eta_c;
}
