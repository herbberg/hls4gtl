#include "algos.h"
#include "requirements.h"
#include "templates.h"

void algos (const eg_obj_t eg[max_obj], const jet_obj_t jet[max_obj], ap_uint<n_algos>& algo)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1

	const ap_uint<1> cond_double_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,2,12>(double_eg_2_requ, eg);
	const ap_uint<1> cond_single_jet_1 = comb_cond<jet_obj_requ_t,jet_obj_t,1,12>(single_jet_2_requ, jet);
	const ap_uint<1> cond_triple_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(triple_eg_2_requ, eg);
	const ap_uint<1> cond_triple_eg_2 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(triple_eg_3_requ, eg);
	const ap_uint<1> cond_quad_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,4,12>(quad_eg_1_requ, eg);

	algo = 0;
	algo |= static_cast<ap_uint<n_algos> > (cond_double_eg_1) << 0;
	algo |= static_cast<ap_uint<n_algos> > (cond_single_jet_1) << 1;
	algo |= static_cast<ap_uint<n_algos> > (cond_triple_eg_1) << 2;
	algo |= static_cast<ap_uint<n_algos> > (cond_triple_eg_2) << 3;
	algo |= static_cast<ap_uint<n_algos> > (cond_quad_eg_1) << 4;

}
