source "./config/config.tcl"

open_project $project
open_solution $solution

export_design -format ip_catalog
