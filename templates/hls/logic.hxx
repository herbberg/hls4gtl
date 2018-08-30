{% extends "header.hxx" %}
{% block code %}
#ifndef impl_logic_h
#define impl_logic_h

#include "../impl/conditions.hxx"

#include <ap_int.h>

namespace impl {

struct logic
{
    typedef ap_uint<1> signal_type;

    void process(const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ], signal_type seeds[N_ALGORITHMS]) const
    {
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1
#pragma HLS ARRAY_PARTITION variable=seeds complete dim=1

        ::impl::conditions cond = {};
        cond.process(eg, jet);

        seeds[0] = cond.double_eg_1;
        seeds[1] = cond.single_jet_1;
        seeds[2] = cond.triple_eg_1;
        seeds[3] = cond.triple_eg_2;
        seeds[4] = cond.quad_eg_1;
    }

}; // struct logic

} // namespace impl

#endif
{% endblock code %}
