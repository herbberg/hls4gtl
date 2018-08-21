#include "algos.h"
#include "requirements.h"
#include "templates.h"

void algos (const eg_obj_t eg[max_obj], const jet_obj_t jet[max_obj], ap_uint<n_algos>& algo)
{
//#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=algo
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1
#pragma HLS unroll

    const size_t n_cond = 5;
    ap_uint<1> cond_matrix[n_cond][max_requ][max_obj];

// requirements versus objects matrix
    comp_requ_vs_obj<ap_uint<1>,eg_obj_requ_t,eg_obj_t,2,12>(cond_matrix[0], double_eg_2_requ, eg);
    comp_requ_vs_obj<ap_uint<1>,jet_obj_requ_t,jet_obj_t,1,12>(cond_matrix[1], single_jet_2_requ, jet);
    comp_requ_vs_obj<ap_uint<1>,eg_obj_requ_t,eg_obj_t,3,12>(cond_matrix[2], triple_eg_2_requ, eg);
    comp_requ_vs_obj<ap_uint<1>,eg_obj_requ_t,eg_obj_t,3,12>(cond_matrix[3], triple_eg_3_requ, eg);
    comp_requ_vs_obj<ap_uint<1>,eg_obj_requ_t,eg_obj_t,4,12>(cond_matrix[4], quad_eg_1_requ, eg);

    ap_uint<1> cond_and_or[n_cond][max_requ][max_obj];
    ap_uint<1> cond_out[n_cond];
    ap_uint<1> cond_out_2_algo[n_cond];

    volatile ap_uint<1> temp_matrix[n_cond][max_requ][max_obj];
    for (size_t i = 0; i < n_cond; i++)    
    {
#pragma HLS unroll    
        for (size_t j = 0; j < max_requ; j++)    
        {
#pragma HLS unroll    
            for (size_t k = 0; k < max_obj; k++)    
            {
#pragma HLS unroll    
// intermediate register
            temp_matrix[i][j][k]=cond_matrix[i][j][k];
            cond_and_or[i][j][k]=temp_matrix[i][j][k];
            }    
        }
    }    
        
// condition AND-OR
    cond_out[0] = comb_cond_and_or<12>(cond_and_or[0]);
    cond_out[1] = comb_cond_and_or<12>(cond_and_or[1]);
    cond_out[2] = comb_cond_and_or<12>(cond_and_or[2]);
    cond_out[3] = comb_cond_and_or<12>(cond_and_or[3]);
    cond_out[4] = comb_cond_and_or<12>(cond_and_or[4]);
    
    volatile ap_uint<1> temp_cond_out[n_cond];
    for (size_t i = 0; i < n_cond; i++)    
    {
#pragma HLS unroll    
// intermediate register
        temp_cond_out[i] = cond_out[i];
        cond_out_2_algo[i] = temp_cond_out[i];
    }    
        
// algos
    algo = 0;
    algo |= static_cast<ap_uint<n_algos> > (cond_out_2_algo[0]) << 0;
    algo |= static_cast<ap_uint<n_algos> > (cond_out_2_algo[1]) << 1;
    algo |= static_cast<ap_uint<n_algos> > (cond_out_2_algo[2]) << 2;
    algo |= static_cast<ap_uint<n_algos> > (cond_out_2_algo[3]) << 3;
    algo |= static_cast<ap_uint<n_algos> > (cond_out_2_algo[4]) << 4;
}
