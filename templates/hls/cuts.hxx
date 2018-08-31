{% extends "header.hxx" %}
{% block code %}
#ifndef impl_cuts_h
#define impl_cuts_h

namespace impl {
namespace cuts {

{% for c in conditions %}
const {{ c.objects[0].type }}_obj_requ_t {{ c.name }}[{{ c.objects|count }}] = {
{%- for o in c.objects %}
    { .n_cuts={{ c.objects|count }}, .n_obj={{ o.slice.maximum }}, .pt={{ o.threshold }}, .eta={{ o.eta }}, .n_eta={{ o.eta|count }}, .phi={{ o.phi}}, .n_phi={{ o.phi|count }} },
{%- endfor %}
};
{% endfor %}

} // namespace cuts
} // namespace impl

#endif
{% endblock code %}
