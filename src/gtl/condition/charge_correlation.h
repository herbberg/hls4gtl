#ifndef gtl_condition_charge_correlation_h
#define gtl_condition_charge_correlation_h

#include <cstdio>

namespace gtl {
namespace condition {

// Charge correlation condition for muon
template<typename T1, typename T2>
void charge_correlation_comp(T1 charge_correlation, const T2 objects[MAX_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

    std::cout << "*** charge_correlation_comp:\n";
// charge correlation double
    for (size_t i = 0; i <= MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        for (size_t j = 0; j <= MAX_MUON_OBJ; j++)
        {
#pragma HLS UNROLL
            if (j != i)
            {
//                 std::cout << "**********************************************************\n";                
//                 std::cout << "objects[i].charge[1]: " << objects[i].charge[1] << "   objects[i].charge[0]: " << objects[i].charge[0] <<"\n";                
//                 std::cout << "objects[j].charge[1]: " << objects[j].charge[1] << "   objects[j].charge[0]: " << objects[j].charge[0] <<"\n";                
//                 std::cout << "objects[" << i << "].charge: " << objects[i].charge << "   objects[" << j << "].charge: "  << objects[j].charge <<"\n";                
                if (objects[i].charge[1] and objects[j].charge[1]) // both charge valid bits have to be true
                {
                    if (objects[i].charge[0] and objects[j].charge[0]) // both charge sign bits are true = like sign
                    {
                        charge_correlation.ls_double[i][j] = true; 
                    }
                    else if (not objects[i].charge[0] and not objects[j].charge[0]) // both charge sign bits are false = like sign
                    {
                        charge_correlation.ls_double[i][j] = true; 
                    }
                    else
                    {
                        charge_correlation.os_double[i][j] = true; // opposite sign
                    }
                }
                else
                {
                    charge_correlation.ls_double[i][j] = false;
                    charge_correlation.os_double[i][j] = false;
                }
//             std::cout << "charge_correlation.ls_double[" << i << "][" << j <<"]: " << charge_correlation.ls_double[i][j] << "   charge_correlation.os_double[" << i << "][" << j << "]: " << charge_correlation.os_double[i][j] <<"\n";                
            }
        }
    }
    std::cout << "charge_correlation.ls_double[0][1]: " << charge_correlation.ls_double[0][1] << "   charge_correlation.os_double[0][1]: " << charge_correlation.os_double[0][1] <<"\n";                
    
// charge correlation triple
    for (size_t i = 0; i <= MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        for (size_t j = 0; j <= MAX_MUON_OBJ; j++)
        {
#pragma HLS UNROLL
            for (size_t k = 0; k <= MAX_MUON_OBJ; k++)
            {
#pragma HLS UNROLL
                if (j != i and k != i and k != j )
                {
                    if (objects[i].charge[1] and objects[j].charge[1] and objects[k].charge[1]) // like sign
                    {
                        if (objects[i].charge[0] and objects[j].charge[0] and objects[k].charge[0])
                        {
                            charge_correlation.ls_triple[i][j][k] = true; 
                        }
                        else if (not objects[i].charge[0] and not objects[j].charge[0] and not objects[k].charge[0]) // like sign
                        {
                            charge_correlation.ls_triple[i][j][k] = true; 
                        }
                        else
                        {
                            charge_correlation.os_triple[i][j][k] = true; // opposite sign
                        }
                    }
                    else
                    {
                        charge_correlation.ls_triple[i][j][k] = false;
                        charge_correlation.os_triple[i][j][k] = false;
                    }
                }
            }
        }
    }
    
// charge correlation quad
    for (size_t i = 0; i <= MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        for (size_t j = 0; j <= MAX_MUON_OBJ; j++)
        {
#pragma HLS UNROLL
            for (size_t k = 0; k <= MAX_MUON_OBJ; k++)
            {
#pragma HLS UNROLL
                for (size_t l = 0; l <= MAX_MUON_OBJ; l++)
                {
#pragma HLS UNROLL
                    if (j != i and k != i and k != j and l != i and l != j and l != k)
                    {
                        if (objects[i].charge[1] and objects[j].charge[1] and objects[k].charge[1] and objects[l].charge[1]) // like sign
                        {
                            if (objects[i].charge[0] and objects[j].charge[0] and objects[k].charge[0] and objects[l].charge[0])
                            {
                                charge_correlation.ls_quad[i][j][k][l] = true; 
                            }
                            else if (not objects[i].charge[0] and not objects[j].charge[0] and not objects[k].charge[0] and not objects[l].charge[0]) // like sign
                            {
                                charge_correlation.ls_quad[i][j][k][l] = true; 
                            }
                            else
                            {
                                charge_correlation.os_quad[i][j][k][l] = true; // opposite sign
                            }
                        }
                        else
                        {
                            charge_correlation.ls_quad[i][j][k][l] = false;
                            charge_correlation.os_quad[i][j][k][l] = false;
                        }
                    }
                }
            }
        }
    }
}

} // namespace condition
} // namespace gtl

#endif
