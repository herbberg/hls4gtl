source {./config/config.tcl}

open_project $project
open_solution $solution

set format {ip_catalog}

export_design -format $format
