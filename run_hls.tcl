open_project hls_impl
set_top algos
add_files src/algos.cpp
add_files src/algos.h
add_files -tb tb/algos_test_4_c_cosim.cpp
add_files -tb tb/byte_vector.h
add_files -tb tb/hex_bytes.h
add_files -tb tb/ostream_utils.cpp
add_files -tb tb/ostream_utils.h
add_files -tb tb/test_vector.cpp
add_files -tb tb/test_vector.h
add_files -tb tb/transaction_writer.h
open_solution "solution1"
set_part {xc7vx690tffg1927-2}
create_clock -period 24 -name default
#source "./hls4gtl/solution1/directives.tcl"
csim_design -compiler gcc
csynth_design
cosim_design -trace_level port -rtl vhdl -tool xsim
export_design -format ip_catalog
exit

