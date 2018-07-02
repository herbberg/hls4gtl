#include "../headers/pt_comp.h"

ap_uint<1> pt_comp (const obj_requ_t *requ, const obj_t *obj){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requ complete dim=0
#pragma HLS ARRAY_PARTITION variable=obj complete dim=0

    return obj->pt >= requ->pt;

}
