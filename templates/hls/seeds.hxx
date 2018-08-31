{% extends "header.hxx" %}
{% block code %}
#ifndef impl_seeds_h
#define impl_seeds_h

#include "../impl/conditions.hxx"

#include <ap_int.h>

namespace impl {
namespace seeds {

struct logic
{
    typedef ap_uint<1> signal_type;

    // seeds signals
  {%- for seed in seeds %}
    signal_type {{ seed.name }};
{%- endfor %}

    void process(const ::impl::conditions::logic& {{ condition_namespace }})
    {
{%- for seed in seeds %}
        {{ seed.name }} = {{ seed.expression }};
{%- endfor %}
    }

    void map(signal_type seeds[N_ALGORITHMS])
    {
#pragma HLS ARRAY_PARTITION variable=seeds complete dim=1
{%- for seed in seeds %}
        seeds[{{ seed.index }}] = {{ seed.name }};
{%- endfor %}
    }

}; // struct logic

} // namespace seeds
} // namespace impl

#endif
{% endblock code %}
