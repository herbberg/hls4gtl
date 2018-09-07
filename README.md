# hls4gtl

Creating GTL with High Level Synthesis

### Usage

    $ git clone https://github.com/herbberg/hls4gtl.git
    $ git checkout <branch/tag>
    $ python manage.py init </path/to/menu/dist> <module_id>
    $ make

The generated symlink ```current_dist``` in the project root directory is the
entry point for the auto generated HLS source files implementing a menu module.
The symlink can be configured either manually, by external scripts or by
using ```manage.py``` which provides also integrity checks on the linked
distribution directory:

    $ python manage.py init|status|clean [args...]

Run individual makefile targets:

    $ make csim|csynth|cosim|export|clean

### HLS directives

Additional HlS directives can be added in ```config/directives.tcl```

### Menu distributions

Use ```tm-distribute``` to create a distribution from an XML trigger menu.

See also: https://github.com/arnobaer/tm-distribute/
