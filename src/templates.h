#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include <cstdlib>
#include "obj.h"
#include "definitions.h"

template<typename T1, typename T2>
ap_uint<1> pt_comp_template(const T1& requ, const T2& obj)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> pt_c = 0;

    pt_c = obj.pt >= requ.pt;

    return pt_c;
}

template<typename T1, typename T2>
ap_uint<1> eta_comp_template(const T1& requ, const T2& obj)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> eta_c = 0;

    if (requ.n_eta == 0)
    {
        eta_c = 1;
    }
    else
    {
        for (size_t i = 0; i < ETA_WINDOWS; i++)
        {
#pragma HLS unroll
#pragma HLS ARRAY_PARTITION variable=requ.eta complete dim=0
            if (obj.eta <= requ.eta[i].upper and obj.eta >= requ.eta[i].lower and i <= requ.n_eta-1)
            {
                eta_c = 1;
            }
        }
    }
    return eta_c;
}

template<typename T1, typename T2>
ap_uint<1> comp_all(const T1& requ, const T2& obj)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> comp_eta = eta_comp_template(requ, obj);
    ap_uint<1> comp_pt = pt_comp_template(requ, obj);

    return comp_eta and comp_pt;

}

template<typename T, size_t X, size_t Y>
void init_2d(T data[X][Y], const T value)
{
    for (size_t i = 0; i < X; ++i)
#pragma HLS unroll
        for (size_t j = 0; j < Y; ++j)
#pragma HLS unroll
            data[i][j] = value;
}

template<typename T1, typename T2, typename T3, size_t NREQ, size_t NOBJ>
void comp_req_vs_obj(T1 data[MAX_REQ][MAX_OBJ], const T2 requirements[MAX_REQ], const T3 objects[MAX_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=data complete dim=0
    init_2d<ap_uint<1>, MAX_REQ, MAX_OBJ>(data, 0x1);
    for (size_t i = 0; i < NREQ; i++)
#pragma HLS unroll
        for (size_t j = 0; j < NOBJ; j++)
#pragma HLS unroll
            data[i][j] = comp_all(requirements[i], objects[j]);
}

/* Workaround to trick HLS loop unrolling */
template<size_t NOBJ>
ap_uint<1> comb_cond_partial(const size_t i, const ap_uint<1> matrix[MAX_REQ][MAX_OBJ])
{
    ap_uint<1> result = false;

    for (size_t j = 0; j < NOBJ; j++)
    {
#pragma HLS unroll
        for (size_t k = 0; k < NOBJ; k++)
        {
#pragma HLS unroll
            for (size_t l = 0; l < NOBJ; l++)
            {
#pragma HLS unroll
                if (j != i and k != i and k != j and l != i and l != j and l != k)
                {
                    result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l];
                }
            }
        }
    }
    return result;
}

template<typename T2, typename T3, size_t NREQ, size_t NOBJ>
ap_uint<1> comb_cond(const T2 requirements[MAX_REQ], const T3 objects[MAX_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> matrix[MAX_REQ][MAX_OBJ];

    // calculate result matrix
    comp_req_vs_obj<ap_uint<1>, T2, T3, NREQ, NOBJ>(matrix, requirements, objects);

    for (size_t i = 0; i < NOBJ; i++)
    {
#pragma HLS unroll
        result |= comb_cond_partial<NOBJ>(i, matrix);
    }

    return result;
}

template<size_t NOBJ>
ap_uint<1> comb_cond_and_or(const ap_uint<1> matrix[MAX_REQ][MAX_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=matrix complete dim=0

    ap_uint<1> result = false;

    for (size_t i = 0; i < NOBJ; i++)
    {
#pragma HLS unroll
        result |= comb_cond_partial<NOBJ>(i, matrix);
    }

    return result;
}

#endif
