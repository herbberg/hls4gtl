# HLS makefile

config_dir = config
project = hls_impl

hlx = vivado_hls_2018.2
remove = rm -rf

.PHONY: all csim csynth cosim export

all: export

$(project):
	$(hlx) $(config_dir)/create_project.tcl

csim: $(project)
	$(hlx) $(config_dir)/$@.tcl

csynth: $(project)
	$(hlx) $(config_dir)/$@.tcl

cosim: csim csynth
	$(hlx) $(config_dir)/$@.tcl

export: cosim
	$(hlx) $(config_dir)/$@.tcl

clean:
	$(remove) $(project)
