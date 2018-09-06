source {./config/config.tcl}

open_project $project
open_solution $solution

set compiler {gcc}
set ldflags {}
set cflags {-clean}

set options {-compiler $$compiler -ldflags $$ldflags $$cflags}
csim_design $options -argv $argv
