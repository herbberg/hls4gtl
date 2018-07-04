#ifndef OBJ_H_
#define OBJ_H_

#include <ap_int.h>

typedef ap_uint<10> pt_t;
typedef ap_int<9> eta_t;
typedef ap_uint<8> phi_t;
typedef ap_uint<3> n_win_t;
typedef ap_uint<1> bool_t;

#define ETA_WINDOWS 5
#define PHI_WINDOWS 2

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
	eta_win_t eta[ETA_WINDOWS];
//	eta_win_t eta_w1;
//	eta_win_t eta_w2;
//	eta_win_t eta_w3;
//	eta_win_t eta_w4;
//	eta_win_t eta_w5;
	n_win_t n_eta;
	phi_win_t phi[PHI_WINDOWS];
//	phi_win_t phi_w1;
//	phi_win_t phi_w2;
	n_win_t n_phi;
};

// **********************************
// new structs for "real" GTL objects

#define ETA_WINDOWS 5
#define PHI_WINDOWS 2

typedef ap_uint<9> eg_pt_t;
typedef ap_uint<11> jet_pt_t;
typedef ap_uint<9> tau_pt_t;
typedef ap_int<8> calo_eta_t;
typedef ap_uint<8> calo_phi_t;
typedef ap_uint<9> muon_pt_t;
typedef ap_int<9> muon_eta_t;
typedef ap_uint<10> muon_phi_t;

struct eg_obj_t {
    eg_pt_t pt;
    calo_eta_t eta;
    calo_phi_t phi;
//    ap_int<2> iso;
};

struct jet_obj_t {
    jet_pt_t pt;
    calo_eta_t eta;
    calo_phi_t phi;
};

struct tau_obj_t {
    tau_pt_t pt;
    calo_eta_t eta;
    calo_phi_t phi;
//    ap_int<2> iso;
};

struct muon_obj_t {
    muon_phi_t phi;
    muon_pt_t pt;
    ap_int<4> qual;
    muon_eta_t eta;
    ap_int<2> iso;
    ap_int<2> charge;
};

struct calo_eta_win_t {
    calo_eta_t upper;
    calo_eta_t lower;
};

struct calo_phi_win_t {
    calo_phi_t upper;
    calo_phi_t lower;
};

struct muon_eta_win_t {
    muon_eta_t upper;
    muon_eta_t lower;
};

struct muon_phi_win_t {
    muon_phi_t upper;
    muon_phi_t lower;
};

struct eg_obj_requ_t {
    eg_pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
//     calo_eta_win_t eta_w1;
//     calo_eta_win_t eta_w2;
//     calo_eta_win_t eta_w3;
//     calo_eta_win_t eta_w4;
//     calo_eta_win_t eta_w5;
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
//     calo_phi_win_t phi_w1;
//     calo_phi_win_t phi_w2;
    ap_int<2> n_phi;
//    ap_uint<2> iso;
};

struct jet_obj_requ_t {
    jet_pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
//     calo_eta_win_t eta_w1;
//     calo_eta_win_t eta_w2;
//     calo_eta_win_t eta_w3;
//     calo_eta_win_t eta_w4;
//     calo_eta_win_t eta_w5;
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
//     calo_phi_win_t phi_w1;
//     calo_phi_win_t phi_w2;
    ap_int<2> n_phi;
};

struct tau_obj_requ_t {
    tau_pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
//     calo_eta_win_t eta_w1;
//     calo_eta_win_t eta_w2;
//     calo_eta_win_t eta_w3;
//     calo_eta_win_t eta_w4;
//     calo_eta_win_t eta_w5;
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
//     calo_phi_win_t phi_w1;
//     calo_phi_win_t phi_w2;
    ap_int<2> n_phi;
//    ap_uint<2> iso;
};

struct muon_obj_requ_t {
	muon_phi_win_t phi_w1;
	muon_phi_win_t phi_w2;
    ap_uint<2> n_phi;
    muon_pt_t pt;
    ap_int<4> qual;
    muon_eta_win_t eta_w1;
    muon_eta_win_t eta_w2;
    muon_eta_win_t eta_w3;
    muon_eta_win_t eta_w4;
    muon_eta_win_t eta_w5;
    ap_uint<3> n_eta;
    ap_uint<2> iso;
    ap_uint<2> charge;
};

#endif
