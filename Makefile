# HLS makefile

config_dir = config
dist_dir = current_dist
project = hls_impl

hlx = vivado_hls
remove = rm -rf

.PHONY: all csim csynth cosim export clean

all: export

$(project): $(dist_dir)
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

distclean: clean
	$(remove) $(dist_dir)
	$(remove) *.log
