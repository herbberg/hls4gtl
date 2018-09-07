# HLS makefile

manage = python manage.py
remove = rm -rf

.PHONY: all csim csynth cosim export clean

all: export

csim:
	$(manage) $@

csynth:
	$(manage) $@

cosim:
	$(manage) $@

export:
	$(manage) $@

clean:
	$(manage) $@

distclean: clean
	$(remove) *.log
