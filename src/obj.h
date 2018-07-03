#ifndef OBJ_H_
#define OBJ_H_

#include <ap_int.h>

typedef ap_uint<8> algos_t;
typedef ap_uint<10> pt_t;
typedef ap_int<9> eta_t;
typedef ap_uint<8> phi_t;
typedef ap_uint<3> n_win_t;
typedef ap_uint<1> bool_t;

//#define ETA_WINDOWS 5
//#define PHI_WINDOWS 2

struct obj_t {
	pt_t pt;
	eta_t eta;
//	phi_t phi;
};

struct phi_win_t {
	phi_t upper;
	phi_t lower;
};

struct eta_win_t {
	eta_t upper;
	eta_t lower;
};

struct obj_requ_t {
	pt_t pt;
	eta_win_t eta_w1;
	eta_win_t eta_w2;
	eta_win_t eta_w3;
	eta_win_t eta_w4;
	eta_win_t eta_w5;
	n_win_t n_eta;
	phi_win_t phi_w1;
	phi_win_t phi_w2;
	n_win_t n_phi;
};

#endif
