#include "../headers/templates.h"
#include "../headers/condition.h"

ap_uint<1> condition (const obj_t objects[MAX_OBJ], const obj_requ_t requirements[MAX_REQ], size_t n_requ, size_t n_obj)
{

#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS INTERFACE ap_ctrl_none port=return

	ap_uint<1> cond_out = 0;

	cond_and_or<ap_uint<1>, MAX_REQ, MAX_OBJ>(cond_out, requirements, objects, n_requ, n_obj);

    return cond_out;

}
