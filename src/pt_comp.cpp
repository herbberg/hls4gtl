#include "pt_comp.h"

ap_uint<1> pt_comp (const obj_requ_t requ, const obj_t obj){

#pragma HLS INTERFACE ap_ctrl_none port=return

    return obj.pt >= requ.pt;

}
