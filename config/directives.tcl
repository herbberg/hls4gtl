# directives for current solution

# src/algos.cpp

set_directive_interface -mode ap_none "algos" eg
set_directive_interface -mode ap_none "algos" jet
set_directive_interface -mode ap_none "algos" algo

set_directive_interface -mode ap_ctrl_none "algos"

set_directive_unroll "algos/loop_init"

# src/templates.h

set_directive_unroll "comb_partial/loop_j"
set_directive_unroll "comb_partial/loop_k"
set_directive_unroll "comb_partial/loop_l"
