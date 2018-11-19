#ifndef tb_charge_correlation_h
#define tb_charge_correlation_h

#include <cstdio>

namespace tb {

/* Workaround to trick HLS loop unrolling */
void charge_corr_quad(const size_t i, const ap_uint<2> charge_corr[MAX_MUON_OBJ], cc_bx_comb_t& cc)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

     for (size_t j = 0; j < MAX_MUON_OBJ; j++)
    {
#pragma HLS UNROLL
        for (size_t k = 0; k < MAX_MUON_OBJ; k++)
        {
#pragma HLS UNROLL
            for (size_t l = 0; l < MAX_MUON_OBJ; l++)
            {
#pragma HLS UNROLL
                if (charge_corr[i][1] and charge_corr[j][1] and charge_corr[k][1] and charge_corr[l][1]) // like sign
                {
                    if (charge_corr[i][0] and charge_corr[j][0] and charge_corr[k][0] and charge_corr[l][0])
                    {
                        cc.cc_quad[i][j][k][l] = 1; 
                    }
                    else if (not charge_corr[i][0] and not charge_corr[j][0] and not charge_corr[k][0] and not charge_corr[l][0]) // like sign
                    {
                        cc.cc_quad[i][j][k][l] = 1; 
                    }
                    else
                    {
                        cc.cc_quad[i][j][k][l] = 2; 
                    }
                }
                else
                {
                    cc.cc_quad[i][j][k][l] = 0; 
                }                    
            }
        }
    }
}

// Charge correlation condition for muon
void charge_correlation_logic(const ap_uint<2> charge_corr[MAX_MUON_OBJ], cc_bx_comb_t& cc)
{
    
// charge correlation double
    for (size_t i = 0; i < MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        for (size_t j = 0; j < MAX_MUON_OBJ; j++)
        {
#pragma HLS UNROLL
            if (charge_corr[i][1] and charge_corr[j][1]) // both charge valid bits have to be true
            {
                if (charge_corr[i][0] and charge_corr[j][0]) // both charge sign bits are true = like sign
                {
                    cc.cc_double[i][j] = 1; 
                }
                else if (not charge_corr[i][0] and not charge_corr[j][0]) // both charge sign bits are false = like sign
                {
                    cc.cc_double[i][j] = 1; 
                }
                else
                {
                    cc.cc_double[i][j] = 2; // opposite sign
            }
            }
            else
            {
                cc.cc_double[i][j] = 0;
            }
        }
    }

// charge correlation triple
    for (size_t i = 0; i < MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        for (size_t j = 0; j < MAX_MUON_OBJ; j++)
        {
#pragma HLS UNROLL
            for (size_t k = 0; k < MAX_MUON_OBJ; k++)
            {
#pragma HLS UNROLL
                if (charge_corr[i][1] and charge_corr[j][1] and charge_corr[k][1]) // like sign
                {
                    if (charge_corr[i][0] and charge_corr[j][0] and charge_corr[k][0])
                    {
                        cc.cc_triple[i][j][k] = 1; 
                    }
                    else if (not charge_corr[i][0] and not charge_corr[j][0] and not charge_corr[k][0]) // like sign
                    {
                        cc.cc_triple[i][j][k] = 1; 
                    }
                    else
                    {
                        cc.cc_triple[i][j][k] = 2; // opposite sign
                    }
                }
                else
                {
                    cc.cc_triple[i][j][k] = 0;
                }
            }
        }
    }

// charge correlation quad
    for (size_t i = 0; i < MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        charge_corr_quad(i, charge_corr, cc);
    }
}

} // namespace tb

#endif
