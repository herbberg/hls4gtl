{% extends "header.hxx" %}
{% block code %}
#ifndef impl_conditions_h
#define impl_conditions_h

#include "../impl/cuts.hxx"

namespace impl {

// TODO: workaround! Implement conditions as structs!
struct conditions
{
    typedef ap_uint<1> signal_type;

    signal_type double_eg_1;
    signal_type single_jet_1;
    signal_type triple_eg_1;
    signal_type triple_eg_2;
    signal_type quad_eg_1;

    void process(const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ])
    {
        double_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,2,12>(cuts::double_eg_2_requ, eg);
        single_jet_1 = comb_cond<jet_obj_requ_t,jet_obj_t,1,12>(cuts::single_jet_2_requ, jet);
        triple_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(cuts::triple_eg_2_requ, eg);
        triple_eg_2 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(cuts::triple_eg_3_requ, eg);
        quad_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,4,12>(cuts::quad_eg_1_requ, eg);
    }
};

} // namespace impl

#endif
{% endblock code %}
