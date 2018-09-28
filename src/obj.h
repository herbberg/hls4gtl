#ifndef OBJ_H_
#define OBJ_H_

#include <cstddef> // for size_t
#include <ap_int.h>
#include "definitions.h"

#include "gtl/utils/range.h"

#include "gtl/object.h"

using namespace gtl;

// objects type definition

struct in_data_t
{
    typedef object::eg eg_type;
    typedef object::jet jet_type;
    typedef object::tau tau_type;
    typedef object::muon muon_type;
    typedef object::asymmetry asymmetry_type;
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

#endif
