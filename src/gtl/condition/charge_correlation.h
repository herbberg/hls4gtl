#ifndef gtl_condition_charge_correlation_h
#define gtl_condition_charge_correlation_h

#include <cstdio>

namespace gtl {
namespace condition {

/* Workaround to trick HLS loop unrolling */
template<typename T1>
void charge_corr_quad(const size_t i, const T1 objects[MAX_MUON_OBJ], ap_uint<1> ls_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ], ap_uint<1> os_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ])
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> result = false;

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
                    ls_quad[i][j][k][l] = false;
                    os_quad[i][j][k][l] = false;
                    if (objects[i].charge[1] and objects[j].charge[1] and objects[k].charge[1] and objects[l].charge[1]) // like sign
                    {
                        if (objects[i].charge[0] and objects[j].charge[0] and objects[k].charge[0] and objects[l].charge[0])
                        {
                            ls_quad[i][j][k][l] = true; 
                        }
                        else if (not objects[i].charge[0] and not objects[j].charge[0] and not objects[k].charge[0] and not objects[l].charge[0]) // like sign
                        {
                            ls_quad[i][j][k][l] = true; 
                        }
                        else
                        {
                            os_quad[i][j][k][l] = true; // opposite sign
                        }
                    }
                    else
                    {
                        ls_quad[i][j][k][l] = false;
                        os_quad[i][j][k][l] = false;
                    }                    
                }
            }
        }
    }
}

// Charge correlation condition for muon
// template<typename T1, typename T2>
// void charge_correlation_logic(const T1 objects[MAX_MUON_OBJ], T2& charge_correlation)
template<typename T1>
void charge_correlation_logic(const T1 objects[MAX_MUON_OBJ], ap_uint<1> ls_double[MAX_MUON_OBJ][MAX_MUON_OBJ], ap_uint<1> os_double[MAX_MUON_OBJ][MAX_MUON_OBJ], ap_uint<1> ls_triple[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ], ap_uint<1> os_triple[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ], ap_uint<1> ls_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ], ap_uint<1> os_quad[MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ][MAX_MUON_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

//     std::cout << "*** charge_correlation_logic:\n";
// charge correlation double
    for (size_t i = 0; i < MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        for (size_t j = 0; j < MAX_MUON_OBJ; j++)
        {
#pragma HLS UNROLL
            ls_double[i][j] = false;
            os_double[i][j] = false;
            if (j != i)
            {
//                 ls_double[i][j] = false;
//                 os_double[i][j] = false;
                if (objects[i].charge[1] and objects[j].charge[1]) // both charge valid bits have to be true
                {
                    if (objects[i].charge[0] and objects[j].charge[0]) // both charge sign bits are true = like sign
                    {
                        ls_double[i][j] = true; 
                    }
                    else if (not objects[i].charge[0] and not objects[j].charge[0]) // both charge sign bits are false = like sign
                    {
                        ls_double[i][j] = true; 
                    }
                    else
                    {
                        os_double[i][j] = true; // opposite sign
                   }
                }
                else
                {
                    ls_double[i][j] = false;
                    os_double[i][j] = false;
                }
            }
        }
    }

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
                    ls_triple[i][j][k] = false;
                    os_triple[i][j][k] = false;
                    if (objects[i].charge[1] and objects[j].charge[1] and objects[k].charge[1]) // like sign
                    {
                        if (objects[i].charge[0] and objects[j].charge[0] and objects[k].charge[0])
                        {
                            ls_triple[i][j][k] = true; 
                        }
                        else if (not objects[i].charge[0] and not objects[j].charge[0] and not objects[k].charge[0]) // like sign
                        {
                            ls_triple[i][j][k] = true; 
                        }
                        else
                        {
                            os_triple[i][j][k] = true; // opposite sign
                        }
                    }
                    else
                    {
                        ls_triple[i][j][k] = false;
                        os_triple[i][j][k] = false;
                    }
                }
            }
        }
    }

// charge correlation quad
    for (size_t i = 0; i <= MAX_MUON_OBJ; i++)
    {
#pragma HLS UNROLL
        charge_corr_quad<T1>(i, objects, ls_quad, os_quad);
    }

//     for (size_t i = 0; i < MAX_MUON_OBJ; i++)
//     {
// #pragma HLS UNROLL
//         for (size_t j = 0; j < MAX_MUON_OBJ; j++)
//         {
// #pragma HLS UNROLL
//             if (j != i)
//             {
//                 charge_correlation.ls_double[i][j] = false;
//                 charge_correlation.os_double[i][j] = false;
// //                 std::cout << "begin => charge_correlation.ls_double[" << i << "][" << j << "]: " << charge_correlation.ls_double[i][j] << "\n";                
// //                 std::cout << "begin => charge_correlation.os_double[" << i << "][" << j << "]: " << charge_correlation.os_double[i][j] << "\n";                
//                 if (objects[i].charge[1] and objects[j].charge[1]) // both charge valid bits have to be true
//                 {
//                     if (objects[i].charge[0] and objects[j].charge[0]) // both charge sign bits are true = like sign
//                     {
//                         charge_correlation.ls_double[i][j] = true; 
// //                         std::cout << "sign bits = 1 => charge_correlation.ls_double[" << i << "][" << j <<"]: " << charge_correlation.ls_double[i][j] << "\n";                
//                     }
//                     else if (not objects[i].charge[0] and not objects[j].charge[0]) // both charge sign bits are false = like sign
//                     {
//                         charge_correlation.ls_double[i][j] = true; 
// //                         std::cout << "sign bits = 0 => charge_correlation.ls_double[" << i << "][" << j <<"]: " << charge_correlation.ls_double[i][j] << "\n";                
//                     }
//                     else
//                     {
//                         charge_correlation.os_double[i][j] = true; // opposite sign
// //                         std::cout << "sign bits not equal => charge_correlation.os_double[" << i << "][" << j << "]: " << charge_correlation.os_double[i][j] << "\n";                
//                     }
//                 }
//                 else
//                 {
//                     charge_correlation.ls_double[i][j] = false;
//                     charge_correlation.os_double[i][j] = false;
//                 }
// //             std::cout << "charge_correlation.ls_double[" << i << "][" << j <<"]: " << charge_correlation.ls_double[i][j] << "   charge_correlation.os_double[" << i << "][" << j << "]: " << charge_correlation.os_double[i][j] <<"\n";                
//             }
//         }
//     }
    
// // charge correlation triple
//     for (size_t i = 0; i <= MAX_MUON_OBJ; i++)
//     {
// #pragma HLS UNROLL
//         for (size_t j = 0; j <= MAX_MUON_OBJ; j++)
//         {
// #pragma HLS UNROLL
//             for (size_t k = 0; k <= MAX_MUON_OBJ; k++)
//             {
// #pragma HLS UNROLL
//                 if (j != i and k != i and k != j )
//                 {
//                     charge_correlation.ls_triple[i][j][k] = false;
//                     charge_correlation.os_triple[i][j][k] = false;
//                     if (objects[i].charge[1] and objects[j].charge[1] and objects[k].charge[1]) // like sign
//                     {
//                         if (objects[i].charge[0] and objects[j].charge[0] and objects[k].charge[0])
//                         {
//                             charge_correlation.ls_triple[i][j][k] = true; 
//                         }
//                         else if (not objects[i].charge[0] and not objects[j].charge[0] and not objects[k].charge[0]) // like sign
//                         {
//                             charge_correlation.ls_triple[i][j][k] = true; 
//                         }
//                         else
//                         {
//                             charge_correlation.os_triple[i][j][k] = true; // opposite sign
//                         }
//                     }
//                     else
//                     {
//                         charge_correlation.ls_triple[i][j][k] = false;
//                         charge_correlation.os_triple[i][j][k] = false;
//                     }
//                 }
//             }
//         }
//     }
//     
// // charge correlation quad
//     for (size_t i = 0; i <= MAX_MUON_OBJ; i++)
//     {
// #pragma HLS UNROLL
//         for (size_t j = 0; j <= MAX_MUON_OBJ; j++)
//         {
// #pragma HLS UNROLL
//             for (size_t k = 0; k <= MAX_MUON_OBJ; k++)
//             {
// #pragma HLS UNROLL
//                 for (size_t l = 0; l <= MAX_MUON_OBJ; l++)
//                 {
// #pragma HLS UNROLL
//                     if (j != i and k != i and k != j and l != i and l != j and l != k)
//                     {
//                         charge_correlation.ls_quad[i][j][k][l] = false;
//                         charge_correlation.os_quad[i][j][k][l] = false;
//                         if (objects[i].charge[1] and objects[j].charge[1] and objects[k].charge[1] and objects[l].charge[1]) // like sign
//                         {
//                             if (objects[i].charge[0] and objects[j].charge[0] and objects[k].charge[0] and objects[l].charge[0])
//                             {
//                                 charge_correlation.ls_quad[i][j][k][l] = true; 
//                             }
//                             else if (not objects[i].charge[0] and not objects[j].charge[0] and not objects[k].charge[0] and not objects[l].charge[0]) // like sign
//                             {
//                                 charge_correlation.ls_quad[i][j][k][l] = true; 
//                             }
//                             else
//                             {
//                                 charge_correlation.os_quad[i][j][k][l] = true; // opposite sign
//                             }
//                         }
//                         else
//                         {
//                             charge_correlation.ls_quad[i][j][k][l] = false;
//                             charge_correlation.os_quad[i][j][k][l] = false;
//                         }
//                     }
//                 }
//             }
//         }
//     }
}

} // namespace condition
} // namespace gtl

#endif
