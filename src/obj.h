#ifndef OBJ_H_
#define OBJ_H_

#include <cstddef> // for size_t
#include <ap_int.h>
#include "definitions.h"
#include "templates.h"

// objects type definition
struct eg_obj_t {
    typedef ap_uint<9> pt_t;
    typedef ap_uint<8> eta_t;
    typedef ap_uint<8> phi_t;
    typedef ap_uint<2> iso_t;
    pt_t pt;
    eta_t eta;
    phi_t phi;
    iso_t iso;
};

struct jet_obj_t {
    typedef ap_uint<11> pt_t;
    typedef ap_uint<8> eta_t;
    typedef ap_uint<8> phi_t;
    pt_t pt;
    eta_t eta;
    phi_t phi;
};

struct tau_obj_t {
    typedef ap_uint<9> pt_t;
    typedef ap_uint<8> eta_t;
    typedef ap_uint<8> phi_t;
    typedef ap_uint<2> iso_t;
    pt_t pt;
    eta_t eta;
    phi_t phi;
    iso_t iso;
};

struct muon_obj_t {
    typedef ap_uint<10> phi_t;
    typedef ap_uint<9> pt_t;
    typedef ap_uint<4> qual_t;
    typedef ap_int<9> eta_t;
    typedef ap_uint<2> iso_t;
    typedef ap_uint<2> charge_t;
    phi_t phi;
    pt_t pt;
    qual_t qual;
    eta_t eta;
    iso_t iso;
    charge_t charge;
};

typedef ap_uint<8> asym_t;
typedef ap_uint<8> centrality_t;
typedef ap_uint<256> extcond_t;

struct in_data_t {
    eg_obj_t eg[MAX_OBJ];
    jet_obj_t jet[MAX_OBJ];
    tau_obj_t tau[MAX_OBJ];
    muon_obj_t muon[MAX_MUON_OBJ]; 
    asym_t asymet;
    asym_t asymht;
    asym_t asymethf;
    asym_t asymhthf;
    centrality_t centrality;
    extcond_t extcond;
};

// requirements type definition
typedef ap_uint<2> n_cuts_t;
typedef ap_uint<4> n_obj_t;

// used eg_obj_t for calos
struct calo_eta_win_t {
    eg_obj_t::eta_t lower;
    eg_obj_t::eta_t upper;
};

struct calo_phi_win_t {
    eg_obj_t::phi_t lower;
    eg_obj_t::phi_t upper;
};

struct muon_eta_win_t {
    muon_obj_t::eta_t lower;
    muon_obj_t::eta_t upper;
};

struct muon_phi_win_t {
    muon_obj_t::phi_t lower;
    muon_obj_t::phi_t upper;
};

struct eg_obj_requ_t {
    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;
    n_cuts_t n_cuts;
    n_obj_t n_obj;
    eg_obj_t::pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
    ap_int<2> n_phi;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];
    ap_uint<1> comp(const eg_obj_t& obj) const
    {
        ap_uint<1> comp_pt = pt_comp_template(*this, obj);
        ap_uint<1> comp_eta = eta_comp_template(*this, obj);
        ap_uint<1> comp_phi = phi_comp_template(*this, obj);
        ap_uint<1> comp_iso = iso_lut[obj.iso];
        return comp_pt and comp_eta and comp_phi and comp_iso;
    };
};

struct jet_obj_requ_t {
    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    n_cuts_t n_cuts;
    n_obj_t n_obj;
    jet_obj_t::pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
    ap_int<2> n_phi;
    ap_uint<1> comp(const jet_obj_t& obj) const
    {
        ap_uint<1> comp_pt = pt_comp_template(*this, obj);
        ap_uint<1> comp_eta = eta_comp_template(*this, obj);
        ap_uint<1> comp_phi = phi_comp_template(*this, obj);
        return comp_pt and comp_eta and comp_phi;
    };
};

struct tau_obj_requ_t {
    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;
    n_cuts_t n_cuts;
    n_obj_t n_obj;
    tau_obj_t::pt_t pt;
    calo_eta_win_t eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    calo_phi_win_t phi[PHI_WINDOWS];
    ap_int<2> n_phi;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];
    ap_uint<1> comp(const tau_obj_t& obj) const
    {
        ap_uint<1> comp_pt = pt_comp_template(*this, obj);
        ap_uint<1> comp_eta = eta_comp_template(*this, obj);
        ap_uint<1> comp_phi = phi_comp_template(*this, obj);
        ap_uint<1> comp_iso = iso_lut[obj.iso];
        return comp_pt and comp_eta and comp_phi and comp_iso;
    };
};

struct muon_obj_requ_t {
    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;
    static const size_t QUAL_LUT_WIDTH = 16;
    enum req_charge_t {
        IGNORE,
        POSITIVE,
        NEGATIVE
    };
    
    n_cuts_t n_cuts;
    n_obj_t n_obj;
    muon_phi_win_t phi[PHI_WINDOWS];
    ap_uint<2> n_phi;
    muon_obj_t::pt_t pt;
    ap_uint<1> qual_lut[QUAL_LUT_WIDTH];
    muon_eta_win_t eta[ETA_WINDOWS];
    ap_uint<3> n_eta;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];
    req_charge_t requested_charge;
    ap_uint<1> comp(const muon_obj_t& obj) const
    {
        ap_uint<1> comp_pt = pt_comp_template(*this, obj);
        ap_uint<1> comp_eta = eta_comp_template(*this, obj);
        ap_uint<1> comp_phi = phi_comp_template(*this, obj);
        ap_uint<1> comp_qual = qual_lut[obj.qual];
        ap_uint<1> comp_iso = iso_lut[obj.iso];
        ap_uint<1> comp_charge = charge_comp_template(*this, obj);
        return comp_pt and comp_eta and comp_phi and comp_qual and comp_iso and comp_phi;
    };
};

#endif
