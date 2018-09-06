#include "algos.h"

#include "definitions.h"
#include "obj.h"

#include "current_dist.h"

void algos(const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], ap_uint<1> algo[N_ALGORITHMS])
{
    // create static logic
    static ::impl::conditions::logic conditions_logic = {};
    static ::impl::seeds::logic seeds_logic = {};

    // update condition states
    conditions_logic.process(eg, jet);

    // update seed states
    seeds_logic.process(conditions_logic);

    loop_init:
    for (size_t i = 0; i <N_ALGORITHMS; i++)
    {
        algo[i] = 0;
    }

    // map seed states to output
    seeds_logic.map(algo);

}
