#ifndef gtl_condition_comb_h
#define gtl_condition_comb_h

namespace gtl {
namespace condition {

template<typename T, size_t X, size_t Y>
void init_2d(T data[X][Y], const T value)
{
    for (size_t i = 0; i < X; ++i)
#pragma HLS unroll
        for (size_t j = 0; j < Y; ++j)
#pragma HLS unroll
            data[i][j] = value;
}

template<typename T1, typename T2, typename T3, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
void comb_matrix(T1 data[MAX_REQ][MAX_OBJ], const T2 requirements[MAX_REQ], const T3 objects[MAX_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=data complete dim=0
    init_2d<ap_uint<1>, MAX_REQ, MAX_OBJ>(data, 0x1);
    for (size_t i = 0; i < NREQ; i++)
#pragma HLS unroll
        for (size_t j = 0; j < MAX_OBJ; j++)
            if (j >= SLICE_MIN and j <= SLICE_MAX)
#pragma HLS unroll
                data[i][j] = requirements[i].comp(objects[j]);
}

/* Workaround to trick HLS loop unrolling */
template<size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb_partial(const size_t i, const ap_uint<1> matrix[MAX_REQ][MAX_OBJ])
{
    ap_uint<1> result = false;

    loop_j:
    for (size_t j = 0; j < MAX_OBJ; j++)
    {
        if (j >= SLICE_MIN and j <= SLICE_MAX)
        {
            loop_k:
            for (size_t k = 0; k < MAX_OBJ; k++)
            {
                if (k >= SLICE_MIN and k <= SLICE_MAX)
                {
                    loop_l:
                    for (size_t l = 0; l < MAX_OBJ; l++)
                    {
                        if (k >= SLICE_MIN and k <= SLICE_MAX)
                        {
                            if (j != i and k != i and k != j and l != i and l != j and l != k)
                            {
                                result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l];
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

/* Combination condition */
template<typename T2, typename T3, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb(const T2 requirements[MAX_REQ], const T3 objects[MAX_OBJ])
{
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> matrix[MAX_REQ][MAX_OBJ];

    // calculate result matrix
    comb_matrix<ap_uint<1>, T2, T3, NREQ, SLICE_MIN, SLICE_MAX>(matrix, requirements, objects);

    for (size_t i = 0; i < MAX_OBJ; i++)
    {
#pragma HLS unroll
        if (i >= SLICE_MIN and i <= SLICE_MAX)
        {
            result |= comb_partial<SLICE_MIN, SLICE_MAX>(i, matrix);
        }
    }

    return result;
}

} // namespace condition
} // namespace gtl

#endif
