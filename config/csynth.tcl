source {./config/config.tcl}

open_project $project
open_solution $solution

set options {}
csynth_design $options
