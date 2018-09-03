#include "algos.h"
#include "requirements.h"
#include "templates.h"

void algos (const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], ap_uint<1> algo[N_ALGORITHMS])
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1
#pragma HLS ARRAY_PARTITION variable=algo complete dim=1

    const ap_uint<1> cond_double_eg_1 = comb_cond<eg_obj_req_t,eg_obj_t,2,12>(double_eg_2_req, eg);
    const ap_uint<1> cond_single_jet_1 = comb_cond<jet_obj_req_t,jet_obj_t,1,12>(single_jet_2_req, jet);
    const ap_uint<1> cond_triple_eg_1 = comb_cond<eg_obj_req_t,eg_obj_t,3,12>(triple_eg_2_req, eg);
    const ap_uint<1> cond_triple_eg_2 = comb_cond<eg_obj_req_t,eg_obj_t,3,12>(triple_eg_3_req, eg);
    const ap_uint<1> cond_quad_eg_1 = comb_cond<eg_obj_req_t,eg_obj_t,4,12>(quad_eg_1_req, eg);

    for (size_t i = 0; i <N_ALGORITHMS; i++)
    {
#pragma HLS unroll
    	algo[i] = 0;
    }

    algo[0] = cond_double_eg_1;
    algo[1] = cond_single_jet_1;
    algo[2] = cond_triple_eg_1;
    algo[3] = cond_triple_eg_2;
    algo[4] = cond_quad_eg_1;

}
