source "./config/config.tcl"

open_project $project
open_solution $solution

cosim_design -trace_level port -rtl vhdl -tool xsim -argv $argv
