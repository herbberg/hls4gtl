#ifndef gtl_input_h
#define gtl_input_h

#include <cstddef> // for size_t
#include <ap_int.h>
#include "definitions.h"

#include "gtl/object.h"

using namespace gtl;

// TODO review

struct in_data_t
{
    typedef object::eg eg_type;
    typedef object::jet jet_type;
    typedef object::tau tau_type;
    typedef object::muon muon_type;
    typedef object::ett ett_type;
    typedef object::htt htt_type;
    typedef object::etm etm_type;
    typedef object::etmhf etmhf_type;
    typedef object::ettem ettem_type;
    typedef object::htm htm_type;
//     typedef object::minimumbias minimumbias_type;
    typedef object::mbt0hfp mbt0hfp_type;
    typedef object::mbt0hfm mbt0hfm_type;
    typedef object::mbt1hfp mbt1hfp_type;
    typedef object::mbt1hfm mbt1hfm_type;    
//     typedef object::asymmetry asymmetry_type;
    typedef object::asymmetry_et asymmetry_et_type;
    typedef object::asymmetry_ht asymmetry_ht_type;
    typedef object::asymmetry_ethf asymmetry_ethf_type;
    typedef object::asymmetry_hthf asymmetry_hthf_type;
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
    ett_type ett[1];
    htt_type htt[1];
    etm_type etm[1];
    etmhf_type etmhf[1];
    ettem_type ettem[1];
    htm_type htm[1];
    mbt0hfp_type mbt0hfp[1];
    mbt0hfm_type mbt0hfm[1];
    mbt1hfp_type mbt1hfp[1];
    mbt1hfm_type mbt1hfm[1];
//     minimumbias_type mbt0hfp[1];
//     minimumbias_type mbt0hfm[1];
//     minimumbias_type mbt1hfp[1];
//     minimumbias_type mbt1hfm[1];
    asymmetry_et_type asymmetry_et[1];
    asymmetry_ht_type asymmetry_ht[1];
    asymmetry_ethf_type asymmetry_ethf[1];
    asymmetry_hthf_type asymmetry_hthf[1];
//     asymmetry_type asymmetry_et[1];
//     asymmetry_type asymmetry_ht[1];
//     asymmetry_type asymmetry_ethf[1];
//     asymmetry_type asymmetry_hthf[1];
    centrality_type centrality;
    external_type external;
};

#endif
