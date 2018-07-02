#include "../headers/comp.h"

ap_uint<1> comp (const obj_requ_t *requ, const obj_t *obj){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requ complete dim=0
#pragma HLS ARRAY_PARTITION variable=obj complete dim=0

	ap_uint<1>  comp_pt = pt_comp(requ, obj);
	ap_uint<1>  comp_eta = eta_comp(requ, obj);

    return comp_eta and comp_pt;

}
