#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include <cstdlib>
#include "comp.h"
#include "definitions.h"

template<typename T, size_t X, size_t Y>
void init_2d(T data[X][Y], const T value)
{
    for (size_t i = 0; i < X; ++i)
#pragma HLS unroll
        for (size_t j = 0; j < Y; ++j)
#pragma HLS unroll
        	data[i][j] = value;
}

//template<typename T2, size_t MAXREQU, size_t MAXOBJ>
template<typename T2, size_t NREQU, size_t NOBJ>
void comp_requ_vs_obj(T2 data[max_requ][max_obj], const obj_requ_t requirements[max_requ], const obj_t objects[max_obj])
{
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=data complete dim=0
	init_2d<ap_uint<1>, max_requ, max_obj>(data, 0x1);
    for (size_t i = 0; i < NREQU; i++)
#pragma HLS unroll
        for (size_t j = 0; j < NOBJ; j++)
#pragma HLS unroll
        	data[i][j] = comp(requirements[i], objects[j]);
}

//template<typename T3, size_t MAXREQU, size_t MAXOBJ>
template<size_t NREQU, size_t NOBJ>
ap_uint<1> cond_and_or(const obj_requ_t requirements[max_requ], const obj_t objects[max_obj])
{
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
	ap_uint<1> data = 0;
	ap_uint<1> comp_out[max_requ][max_obj];
	comp_requ_vs_obj<ap_uint<1>, NREQU, NOBJ>(comp_out, requirements, objects);
//#pragma HLS PIPELINE II=1
	for (size_t i = 0; i < NOBJ; i++) {
#pragma HLS unroll
        for (size_t j = 0; j < NOBJ; j++) {
#pragma HLS unroll
            for (size_t k = 0; k < NOBJ; k++) {
#pragma HLS unroll
                for (size_t l = 0; l < NOBJ; l++) {
#pragma HLS unroll
                	if (j!=i && k!=i && k!=j && l!=i && l!=j && l!=k) {
                    	data |= comp_out[0][i] & comp_out[1][j] & comp_out[2][k] & comp_out[3][l];
                    }
                }
            }
        }
    }
	return data;
}

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

	for (size_t i = 0; i < ETA_WINDOWS; i++) {
#pragma HLS unroll
		if (obj.eta <= requ.eta[i].upper and obj.eta >= requ.eta[i].lower and i <= requ.n_eta) {
			eta_c = 1;
		}
	}
	return eta_c;
}

#endif
