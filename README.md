# hls4gtl

Creating GTL with High Level Synthesis

### Usage

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

### Contribute

Project directory structure:

* `config/` ... vivado_hls TCL control scripts
* `src/` ... all design sources
* `tb/` ... test bench and unit test sources
* `utils/` ... various utilities
* `manage.py` ... project manager application
* `Makefile` ... wrapper for project manager

Source code structure:

All GTL specific components are part of the `gtl` namespace.

All directories and filenames reflect the underlying namespaces and structs.

#### Comparators

Comparators are implemented as templates, located in the `gtl::comparator` namespace.

Current implementation:

* `gtl::comparator::pt` ... pt threshold comparator
* `gtl::comparator::eta` ... eta window comparator
* `gtl::comparator::phi` ... phi window comparator
* `gtl::comparator::charge` ... charge comparator

#### Objects

Objects are implemented as structs, located in the `gtl::object` namespace.

Current implementation:

* `gtl::object::eg` ... egamma object container
* `gtl::object::jet` ... jet object container
* `gtl::object::tau` ... tau object container
* `gtl::object::muon` ... muon object container
* `gtl::object::centrality` ... centrality signal vector
* `gtl::object::external` ... external signal vector

#### Cuts

Cuts (requirements) are implemented as structs, located in the `gtl::cut` namespace.

Current implementation:

* `gtl::cut::eg` ... egamma object cuts
* `gtl::cut::jet` ... jet object cuts
* `gtl::cut::tau` ... tau object cuts
* `gtl::cut::muon` ... muon object cuts
* `gtl::cut::centrality` ... centrality signal cut
* `gtl::cut::external` ... external signal cut

#### Conditions

Conditions are (currently) implemented as functions, located in the `gtl::condition` namespace.

Current implementation:

* `gtl::condition::comb` ... combination condition
* `gtl::condition::signal` ... signal condition for centrality and external signals

#### Utilities

Generic implementations af functions and structs are located in the `gtl::utils` namespace.

Current implementation:

* `gtl::utils::math` ... constant expression preprocessor math functions
* `gtl::utils::range` ... range container template (minimum, maximum)
* `gtl::utils::signal_vector` ... signal vector template (access single bits of `ap_uint` vector)

Test bench structure:

* `tb/algos_test.h/cpp` ... main automated test bench
* `tb/byte_vector.h` ... arbitrary integer emulation
* `tb/bytelify.h/cpp` ... arbitrary hex string to byte vector conversion
* `tb/ostream_utils.h/cpp` ... object string stream conversions
* `tb/test_vector.h/cpp` ... test vector file reader/parser
