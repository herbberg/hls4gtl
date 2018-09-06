source "./config/config.tcl"

open_project $project
open_solution $solution

csim_design -O -clean -compiler gcc -argv $argv
