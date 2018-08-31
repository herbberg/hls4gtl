{% extends "header.hxx" %}
{% block code %}
#ifndef impl_conditions_h
#define impl_conditions_h

#include "../impl/cuts.hxx"

namespace impl {
namespace conditions {

// TODO: workaround! Implement conditions as structs!
struct logic
{
    typedef ap_uint<1> signal_type;

    // condition signals
{% for condition in conditions %}
    signal_type {{ condition.name }};
{%- endfor %}

    void process(const eg_obj_t eg[MAX_OBJ], const jet_obj_t jet[MAX_OBJ])
    {
#pragma HLS ARRAY_PARTITION variable=eg complete dim=1
#pragma HLS ARRAY_PARTITION variable=jet complete dim=1
{% for c in conditions %}
        {{ c.name }} = {{ c.type }}<{{ c.objects[0].type }}_obj_requ_t, {{ c.objects[0].type }}_obj_t ,{{ c.objects|count }}, 12>(cuts::{{ c.name }}, {{ c.objects[0].type }});
{%- endfor %}
    }
};

} // namespace conditions
} // namespace impl

#endif
{% endblock code %}
