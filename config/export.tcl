source {./config/config.tcl}

open_project $project
open_solution $solution

set format {ip_catalog}

set options {-format $$format}
export_design $options
