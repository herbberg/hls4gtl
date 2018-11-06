# hls4gtl

Creating GTL with High Level Synthesis

## Usage

    $ git clone https://github.com/herbberg/hls4gtl.git
    $ git checkout <branch/tag>
    $ python manage.py init </path/to/menu/dist> <module_id>
    $ python manage.py export

The generated symlink ```current_dist``` in the project root directory is the
entry point for the auto generated HLS source files implementing a menu module.
The symlink can be configured either manually, by external scripts or by
using ```manage.py``` which provides also integrity checks on the linked
distribution directory:

    $ python manage.py init|status|reset [...]

To generate a solution, run simulation or export the IP core use the HLS specific comamnds:

    $ python manage.py csim|csynth|cosim|export|clean [...]

### C/Co simulation

Running ```manage.py csim``` or ```manage.py csim``` automatically crawls for test vector files in the menu distribution's ```testvectors``` directory. The search pattern is ```TestVector*.txt```. Every located test vector is loaded by the C/Co simulation.

To run the C simulation with one or more custom test vectors apply them using the ```--testvector <file ...>``` option.

    $ python manage.py csim --testvector custom_testvector.txt

### HLS directives

Additional HlS directives can be added in ```config/directives.tcl```

### Menu distributions

Use ```tm-distribute``` to create a distribution from an XML trigger menu.

See also: https://github.com/arnobaer/tm-distribute/

## Contributing

If you want to help improve hls4gtl you can start by reading this [guide](CONTRIBUTING.md)
