#ifndef OBJ_H_
#define OBJ_H_

#include <ap_int.h>

// **********************************
// new structs for "real" GTL objects

#define ETA_WINDOWS 5
#define PHI_WINDOWS 2

typedef ap_uint<9> eg_pt_t;
typedef ap_uint<2> eg_iso_t;
typedef ap_uint<11> jet_pt_t;
typedef ap_uint<9> tau_pt_t;
typedef ap_uint<2> tau_iso_t;
typedef ap_int<8> calo_eta_t;
typedef ap_uint<8> calo_phi_t;
typedef ap_uint<9> muon_pt_t;
typedef ap_int<9> muon_eta_t;
typedef ap_uint<10> muon_phi_t;
typedef ap_uint<4> muon_qual_t;
typedef ap_uint<2> muon_iso_t;
typedef ap_uint<2> muon_charge_t;

typedef ap_uint<2> n_req_t;
typedef ap_uint<4> n_obj_t;



struct eg_obj_t {
    eg_pt_t pt;
    calo_eta_t eta;
//    calo_phi_t phi;
//    eg_iso_t iso;
};

struct jet_obj_t {
    jet_pt_t pt;
    calo_eta_t eta;
//    calo_phi_t phi;
};

struct tau_obj_t {
    tau_pt_t pt;
    calo_eta_t eta;
//    calo_phi_t phi;
//    tau_iso_t iso;
};

struct muon_obj_t {
    muon_phi_t phi;
    muon_pt_t pt;
    muon_qual_t qual;
    muon_eta_t eta;
    muon_iso_t iso;
    muon_charge_t charge;
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

struct eg_obj_req_t {
    n_req_t n_req;
    n_obj_t n_obj;
    eg_pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
    ap_int<2> n_phi;
//    eg_iso_t iso;
};

struct jet_obj_req_t {
    n_req_t n_req;
    n_obj_t n_obj;
    jet_pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
    ap_int<2> n_phi;
};

struct tau_obj_req_t {
    n_req_t n_req;
    n_obj_t n_obj;
    tau_pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
    ap_int<2> n_phi;
//    tau_iso_t iso;
};

struct muon_obj_req_t {
    n_req_t n_req;
    n_obj_t n_obj;
    muon_phi_win_t phi[PHI_WINDOWS];
    ap_uint<2> n_phi;
    muon_pt_t pt;
    muon_qual_t qual;
    muon_eta_win_t eta[ETA_WINDOWS];
    ap_uint<3> n_eta;
    muon_iso_t iso;
    muon_charge_t charge;
};

#endif
