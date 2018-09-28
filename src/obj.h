#ifndef OBJ_H_
#define OBJ_H_

#include <cstddef> // for size_t
#include <ap_int.h>
#include "definitions.h"

#include "gtl/utils/range.h"

#include "gtl/object/centrality.h"
#include "gtl/object/external.h"

#include "gtl/comparator/pt.h"
#include "gtl/comparator/eta.h"
#include "gtl/comparator/phi.h"
#include "gtl/comparator/charge.h"

using namespace gtl;

// objects type definition
struct eg_obj_t
{
    typedef ap_uint<9> pt_type;
    typedef ap_int<8> eta_type;
    typedef ap_uint<8> phi_type;
    typedef ap_uint<2> iso_type;

    pt_type pt;
    eta_type eta;
    phi_type phi;
    iso_type iso;
};

struct jet_obj_t
{
    typedef ap_uint<11> pt_type;
    typedef ap_int<8> eta_type;
    typedef ap_uint<8> phi_type;

    pt_type pt;
    eta_type eta;
    phi_type phi;
};

struct tau_obj_t
{
    typedef ap_uint<9> pt_type;
    typedef ap_int<8> eta_type;
    typedef ap_uint<8> phi_type;
    typedef ap_uint<2> iso_type;

    pt_type pt;
    eta_type eta;
    phi_type phi;
    iso_type iso;
};

struct muon_obj_t
{
    typedef ap_uint<10> phi_type;
    typedef ap_uint<9> pt_type;
    typedef ap_uint<4> quality_type;
    typedef ap_int<9> eta_type;
    typedef ap_uint<2> iso_type;
    typedef ap_uint<2> charge_type;

    phi_type phi;
    pt_type pt;
    quality_type qual;
    eta_type eta;
    iso_type iso;
    charge_type charge;
};

struct asymmetry_t
{
    typedef ap_uint<8> count_type;

    count_type count;
};

struct in_data_t
{
    typedef eg_obj_t eg_type;
    typedef jet_obj_t jet_type;
    typedef tau_obj_t tau_type;
    typedef muon_obj_t muon_type;
    typedef asymmetry_t asymmetry_type;
    typedef object::centrality centrality_type;
    typedef object::external external_type;
    typedef size_t size_type;

    const static size_type EG_SIZE = 12;
    const static size_type JET_SIZE = 12;
    const static size_type TAU_SIZE = 12;
    const static size_type MUON_SIZE = 8;

    eg_type eg[EG_SIZE];
    jet_type jet[JET_SIZE];
    tau_type tau[TAU_SIZE];
    muon_type muon[MUON_SIZE];
    asymmetry_type asymmetry_et;
    asymmetry_type asymmetry_ht;
    asymmetry_type asymmetry_ethf;
    asymmetry_type asymmetry_hthf;
    centrality_type centrality;
    external_type external;
};

// requirements type definition
typedef ap_uint<2> n_cuts_t;
typedef ap_uint<4> n_obj_t;

struct eg_obj_requ_t
{
    typedef eg_obj_t object_type;
    typedef utils::range<object_type::eta_type> eta_range_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;

    n_cuts_t n_cuts;
    n_obj_t slice[2];
    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    eta_range_type eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    phi_range_type phi[PHI_WINDOWS];
    ap_int<2> n_phi;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_eta = comparator::eta(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        ap_uint<1> comp_iso = iso_lut[object.iso];
        return comp_pt and comp_eta and comp_phi and comp_iso;
    };
};

struct jet_obj_requ_t
{
    typedef jet_obj_t object_type;
    typedef utils::range<object_type::eta_type> eta_range_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;

    n_cuts_t n_cuts;
    n_obj_t slice[2];
    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    eta_range_type eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    phi_range_type phi[PHI_WINDOWS];
    ap_int<2> n_phi;

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_eta = comparator::eta(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        return comp_pt and comp_eta and comp_phi;
    };
};

struct tau_obj_requ_t
{
    typedef tau_obj_t object_type;
    typedef utils::range<object_type::eta_type> eta_range_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;

    n_cuts_t n_cuts;
    n_obj_t slice[2];
    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    eta_range_type eta[ETA_WINDOWS];
    ap_int<3> n_eta;
    phi_range_type phi[PHI_WINDOWS];
    ap_int<2> n_phi;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_eta = comparator::eta(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        ap_uint<1> comp_iso = iso_lut[object.iso];
        return comp_pt and comp_eta and comp_phi and comp_iso;
    };
};

struct muon_obj_requ_t
{
    typedef muon_obj_t object_type;
    typedef utils::range<object_type::eta_type> eta_range_type;
    typedef utils::range<object_type::phi_type> phi_range_type;

    enum req_charge_type
    {
        IGNORE,
        POSITIVE,
        NEGATIVE
    };

    static const size_t ETA_WINDOWS = 5;
    static const size_t PHI_WINDOWS = 2;
    static const size_t ISO_LUT_WIDTH = 4;
    static const size_t QUALITY_LUT_WIDTH = 16;

    n_cuts_t n_cuts;
    n_obj_t slice[2];
    object_type::pt_type pt;
    comparison_mode_t comparison_mode;
    eta_range_type eta[ETA_WINDOWS];
    ap_uint<3> n_eta;
    phi_range_type phi[PHI_WINDOWS];
    ap_uint<2> n_phi;
    ap_uint<1> iso_lut[ISO_LUT_WIDTH];
    ap_uint<1> qual_lut[QUALITY_LUT_WIDTH];
    req_charge_type requested_charge;

    ap_uint<1> comp(const object_type& object) const
    {
        ap_uint<1> comp_pt = comparator::pt(*this, object);
        ap_uint<1> comp_eta = comparator::eta(*this, object);
        ap_uint<1> comp_phi = comparator::phi(*this, object);
        ap_uint<1> comp_qual = qual_lut[object.qual];
        ap_uint<1> comp_iso = iso_lut[object.iso];
        ap_uint<1> comp_charge = comparator::charge(*this, object);
        return comp_pt and comp_eta and comp_phi and comp_qual and comp_iso and comp_phi;
    };
};

#endif
