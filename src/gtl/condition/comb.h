#ifndef gtl_condition_comb_h
#define gtl_condition_comb_h

namespace gtl {
namespace condition {
   
template<typename T, size_t X, size_t Y>
void init_2d(T data[X][Y], const T value)
{
    for (size_t i = 0; i < X; ++i)
#pragma HLS UNROLL
        for (size_t j = 0; j < Y; ++j)
#pragma HLS UNROLL
            data[i][j] = value;
}

template<typename T1, typename T2, typename T3, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
void comb_matrix(T1 data[MAX_REQ][SLICE_MAX-SLICE_MIN+1], const T2 requirements[MAX_REQ], const T3 objects[SLICE_MAX-SLICE_MIN+1])
{
#pragma HLS INTERFACE ap_ctrl_none port=data
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=data complete dim=0

    init_2d<ap_uint<1>, MAX_REQ, SLICE_MAX-SLICE_MIN+1>(data, 0x1);
    for (size_t i = 0; i < NREQ; i++)
#pragma HLS UNROLL
        for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
#pragma HLS UNROLL
                data[i][j] = requirements[i].comp(objects[j]);
}

/* Workaround to trick HLS loop unrolling */
template<size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb_partial(const size_t i, const ap_uint<1> matrix[MAX_REQ][SLICE_MAX-SLICE_MIN+1])
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> result = false;

//    std::cerr << "result comb_partial matrix[0][0]: " << matrix[0][0] << "\n";

    for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
    {
#pragma HLS UNROLL
        for (size_t k = SLICE_MIN; k <= SLICE_MAX; k++)
        {
#pragma HLS UNROLL
            for (size_t l = SLICE_MIN; l <= SLICE_MAX; l++)
            {
#pragma HLS UNROLL
                if (j != i and k != i and k != j and l != i and l != j and l != k)
                {
                    result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l];
                }
            }
        }
    }
    
//     std::cerr << "result comb_partial: " << result << "\n";
    
    return result;
}

/* Combination condition */
template<typename T2, typename T3, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb(const T2 requirements[MAX_REQ], const T3 objects[MAX_OBJ])    
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> matrix[MAX_REQ][SLICE_MAX-SLICE_MIN+1];

    // calculate result matrix
    comb_matrix<ap_uint<1>, T2, T3, NREQ, SLICE_MIN, SLICE_MAX>(matrix, requirements, objects);
    
    for (size_t i = SLICE_MIN; i <= SLICE_MAX; i++)
    {
#pragma HLS UNROLL
        result |= comb_partial<SLICE_MIN, SLICE_MAX>(i, matrix);
    }

//     std::cerr << "result comb: " << result << "\n";
    
    return result;
}

template<typename T1, typename T2, size_t SLICE_MIN, size_t SLICE_MAX, size_t RANGE >
ap_uint<1> comb_partial_muon_double(const size_t i, const ap_uint<1> matrix[MAX_REQ][RANGE], const T1 requirements[MAX_REQ], const T2 charge_correlation)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> charge_comp[RANGE][RANGE] = {false};

    for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
    {
#pragma HLS UNROLL
        if (j != i)
        {
//             std::cout << "*** comb_partial_muon_double:\n";
//             std::cout << "requirements[0].requested_charge_correlation: " << requirements[0].requested_charge_correlation << "\n";
//             std::cout << "charge_correlation.ls_double[" << i << "][" << j << "]: " << charge_correlation.ls_double[i][j] << "\n";
//             std::cout << "charge_correlation.os_double[" << i << "][" << j << "]: " << charge_correlation.os_double[i][j] << "\n";
//             if (charge_correlation.ls_double[i,j] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::LS)
            if (charge_correlation.ls_double[i][j] and requirements[0].requested_charge_correlation == 0)
            {
                charge_comp[i][j] = true;
            }
//             else if (charge_correlation.os_double[i,j] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::OS)
            else if (charge_correlation.os_double[i][j] and requirements[0].requested_charge_correlation == 1)
            {
                charge_comp[i][j] = true;
            }
//             else if (requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::IGN)
            else if (requirements[0].requested_charge_correlation == 2)
            {
                charge_comp[i][j] = true;
            }
            else
            {
                charge_comp[i][j] = false;
            }
            result |= matrix[0][i] and matrix[1][j] and charge_comp[i][j];
        }
    }
    return result;
}

template<typename T1, typename T2, size_t SLICE_MIN, size_t SLICE_MAX, size_t RANGE >
ap_uint<1> comb_partial_muon_triple(const size_t i, const ap_uint<1> matrix[MAX_REQ][RANGE], const T1 requirements[MAX_REQ], const T2 charge_correlation)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> charge_comp[RANGE][RANGE][RANGE] = {false};

    for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
    {
#pragma HLS UNROLL
        for (size_t k = SLICE_MIN; k <= SLICE_MAX; k++)
        {
#pragma HLS UNROLL
            if (j != i and k != i and k != j )
            {
//                 if (charge_correlation.ls_triple[i,j,k] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::LS)
                if (charge_correlation.ls_triple[i][j][k] and requirements[0].requested_charge_correlation == 0)
                {
                    charge_comp[i][j][k] = true;
                }
//                 else if (charge_correlation.os_triple[i,j,k] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::OS)
                else if (charge_correlation.os_triple[i][j][k] and requirements[0].requested_charge_correlation == 1)
                {
                    charge_comp[i][j][k] = true;
                }
//                 else if (requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::IGN)
                else if (requirements[0].requested_charge_correlation == 2)
                {
                    charge_comp[i][j][k] = true;
                }
                else
                {
                    charge_comp[i][j][k] = false;
                }
                result |= matrix[0][i] and matrix[1][j]  and matrix[2][k] and charge_comp[i][j][k];
            }
        }
    }
    return result;
}

template<typename T1, typename T2, size_t SLICE_MIN, size_t SLICE_MAX, size_t RANGE >
ap_uint<1> comb_partial_muon_quad(const size_t i, const ap_uint<1> matrix[MAX_REQ][RANGE], const T1 requirements[MAX_REQ], const T2 charge_correlation)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> charge_comp[RANGE][RANGE][RANGE][RANGE] = {false};

    for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
    {
#pragma HLS UNROLL
        for (size_t k = SLICE_MIN; k <= SLICE_MAX; k++)
        {
#pragma HLS UNROLL
            for (size_t l = SLICE_MIN; l <= SLICE_MAX; l++)
            {
#pragma HLS UNROLL
                if (j != i and k != i and k != j and l != i and l != j and l != k)
                {
//                     if (charge_correlation.ls_quad[i,j,k,l] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::LS)
                    if (charge_correlation.ls_quad[i][j][k][l] and requirements[0].requested_charge_correlation == 0)
                    {
                        charge_comp[i][j][k][l] = true;
                    }
//                     else if (charge_correlation.os_quad[i,j,k,l] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::OS)
                    else if (charge_correlation.os_quad[i][j][k][l] and requirements[0].requested_charge_correlation == 1)
                    {
                        charge_comp[i][j][k][l] = true;
                    }
//                     else if (requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::IGN)
                    else if (requirements[0].requested_charge_correlation == 2)
                    {
                        charge_comp[i][j][k][l] = true;
                    }
                    else
                    {
                        charge_comp[i][j][k][l] = false;
                    }
                    result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l] and charge_comp[i][j][k][l];
                }
            }
        }
    }
    return result;
}

// /* Workaround to trick HLS loop unrolling */
// template<typename T1, typename T2, size_t SLICE_MIN, size_t SLICE_MAX, size_t RANGE >
// ap_uint<1> comb_partial_muon(const size_t i, const ap_uint<1> matrix[MAX_REQ][RANGE], const T1 requirements[MAX_REQ], const T2 charge_correlation)
// {
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
// 
//     ap_uint<1> result = false;
//     ap_uint<1> charge_comp_double[RANGE][RANGE] = {false};
//     ap_uint<1> charge_comp_triple[RANGE][RANGE][RANGE] = {false};
//     ap_uint<1> charge_comp_quad[RANGE][RANGE][RANGE][RANGE] = {false};
// 
//     switch(requirements[0].n_cuts)
//     {
//         case 2:
//             for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
//             {
// #pragma HLS UNROLL
//                 if (j != i)
//                 {
//                     if (charge_correlation.ls_double[i,j] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::LS)
//                     {
//                         charge_comp_double[i,j] = true;
//                     }
//                     else if (charge_correlation.os_double[i,j] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::OS)
//                     {
//                         charge_comp_double[i,j] = true;
//                     }
//                     else if (requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::IGN)
//                     {
//                         charge_comp_double[i,j] = true;
//                     }
//                     else
//                     {
//                         charge_comp_double[i,j] = false;
//                     }
//                     result |= matrix[0][i] and matrix[1][j] and charge_comp_double[i][j];
//                 }
//             };
//         case 3:
//             for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
//             {
// #pragma HLS UNROLL
//                 for (size_t k = SLICE_MIN; k <= SLICE_MAX; k++)
//                 {
// #pragma HLS UNROLL
//                     if (j != i and k != i and k != j )
//                     {
//                         if (charge_correlation.ls_.triple[i,j,k] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::LS)
//                         {
//                             charge_comp_triple[i,j,k] = true;
//                         }
//                         else if (charge_correlation.os_.triple[i,j,k] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::OS)
//                         {
//                             charge_comp_triple[i,j,k] = true;
//                         }
//                         else if (requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::IGN)
//                         {
//                             charge_comp_triple[i,j,k] = true;
//                         }
//                         else
//                         {
//                             charge_comp_triple[i,j,k] = false;
//                         }
//                         result |= matrix[0][i] and matrix[1][j]  and matrix[2][k] and charge_comp_triple[i][j][k];
//                     }
//                 }
//             };
//         case 4:
//             for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
//             {
// #pragma HLS UNROLL
//                 for (size_t k = SLICE_MIN; k <= SLICE_MAX; k++)
//                 {
// #pragma HLS UNROLL
//                     for (size_t l = SLICE_MIN; l <= SLICE_MAX; l++)
//                     {
// #pragma HLS UNROLL
//                         if (j != i and k != i and k != j and l != i and l != j and l != k)
//                         {
//                             if (charge_correlation.ls_quad[i,j,k,l] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::LS)
//                             {
//                                 charge_comp_quad[i,j,k,l] = true;
//                             }
//                             else if (charge_correlation.os_.quad[i,j,k,l] and requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::OS)
//                             {
//                                 charge_comp_quad[i,j,k,l] = true;
//                             }
//                             else if (requirements[0].requested_charge_correlation == gtl::object::charge_correlation::value::IGN)
//                             {
//                                 charge_comp_quad[i,j,k,l] = true;
//                             }
//                             else
//                             {
//                                 charge_comp_quad[i,j,k,l] = false;
//                             }
//                             result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l] and charge_comp_quad[i][j][k][l];
//                         }
//                     }
//                 }
//             };
//     }
// 
//     return result;
// }
// 
/* Combination condition for muon*/
template<typename T1, typename T2, typename T3, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb_muon(const T1 requirements[MAX_REQ], const T2 objects[MAX_MUON_OBJ], const T3 charge_correlation)    
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

    const size_t range = SLICE_MAX - SLICE_MIN + 1;
    
    std::cout << "*** comb_muon:\n";
//     std::cout << "RANGE: " << range << "\n";
//     std::cout << "SLICE_MIN: " << SLICE_MIN << "\n";
//     std::cout << "SLICE_MAX: " << SLICE_MAX << "\n";
    std::cout << "charge_correlation.ls_double[0][1]: " << charge_correlation.ls_double[0][1] << "   charge_correlation.os_double[0][1]: " << charge_correlation.os_double[0][1] <<"\n";                
    
    ap_uint<1> result = false;
    ap_uint<1> matrix[MAX_REQ][range];

    // calculate result matrix
    comb_matrix<ap_uint<1>, T1, T2, NREQ, SLICE_MIN, SLICE_MAX>(matrix, requirements, objects);
    
    for (size_t i = SLICE_MIN; i <= SLICE_MAX; i++)
    {
#pragma HLS UNROLL
        if (requirements[0].n_cuts == 2)
        {
            result |= comb_partial_muon_double<T1, T3, SLICE_MIN, SLICE_MAX, range>(i, matrix, requirements, charge_correlation);
        }
        else if (requirements[0].n_cuts == 3)
        {
            result |= comb_partial_muon_triple<T1, T3, SLICE_MIN, SLICE_MAX, range>(i, matrix, requirements, charge_correlation);
        }
        else if (requirements[0].n_cuts == 4)
        {
            result |= comb_partial_muon_quad<T1, T3, SLICE_MIN, SLICE_MAX, range>(i, matrix, requirements, charge_correlation);
        }
    }

    return result;
}

} // namespace condition
} // namespace gtl

#endif
