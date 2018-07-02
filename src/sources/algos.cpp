#include "../headers/algos.h"
#include "../headers/requirements.h"
#include "../headers/templates.h"

void algos (const obj_t eg[max_obj], const obj_t jet[max_obj], ap_uint<n_algos>& algo)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1

	const ap_uint<1> cond_double_eg_1 = cond_and_or<2,7>(double_eg_1_requ, eg);
//	const ap_uint<1> cond_double_eg_1 = condition(eg, double_eg_1_requ, 2, 9); // neun Objekte max. !!!
	const ap_uint<1> cond_single_jet_1 = cond_and_or<1,7>(single_jet_1_requ, jet);
//	const ap_uint<1> cond_single_jet_1 = condition(jet, single_jet_1_requ, 1, 9);
	const ap_uint<1> cond_triple_eg_1 = cond_and_or<3,7>(triple_eg_1_requ, eg);
//	const ap_uint<1> cond_triple_eg_1 = condition(eg, triple_eg_1_requ, 3, 9);

	algo = 0;
	algo |= static_cast<ap_uint<n_algos> > (cond_double_eg_1) << 0;
	algo |= static_cast<ap_uint<n_algos> > (cond_single_jet_1) << 1;
	algo |= static_cast<ap_uint<n_algos> > (cond_triple_eg_1) << 2;

}
