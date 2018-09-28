# Contributing to hls4gtl

## Project structure

* `config/` ... vivado_hls TCL control scripts
* `src/` ... all design sources
* `tb/` ... test bench and unit test sources
* `utils/` ... various utilities
* `manage.py` ... project manager application
* `Makefile` ... wrapper for project manager

## Source code structure

All GTL specific source code files are located in the project's `src/` directory.

All directories and filenames reflect the underlying namespaces and structs.

All GTL specific components are part of the `gtl` namespace.

All distinctive components are part of a sub namespace. Currenly there are fife component namespaces available:

* `gtl::comparator` ... comparators
* `gtl::object` ... object containers
* `gtl::cut` ... object cuts
* `gtl::condition` ... conditions
* `gtl::utils` ... generic utilities

### Comparators

Comparators are implemented as templates, located in the `gtl::comparator` namespace.

Current implementation:

* `gtl::comparator::pt` ... pt threshold comparator
* `gtl::comparator::eta` ... eta window comparator
* `gtl::comparator::phi` ... phi window comparator
* `gtl::comparator::charge` ... charge comparator

### Objects

Objects are implemented as structs, located in the `gtl::object` namespace.

Current implementation:

* `gtl::object::eg` ... egamma object container
* `gtl::object::jet` ... jet object container
* `gtl::object::tau` ... tau object container
* `gtl::object::muon` ... muon object container
* `gtl::object::centrality` ... centrality signal vector
* `gtl::object::external` ... external signal vector

### Cuts

Cuts (requirements) are implemented as structs, located in the `gtl::cut` namespace.

Current implementation:

* `gtl::cut::eg` ... egamma object cuts
* `gtl::cut::jet` ... jet object cuts
* `gtl::cut::tau` ... tau object cuts
* `gtl::cut::muon` ... muon object cuts
* `gtl::cut::centrality` ... centrality signal cut
* `gtl::cut::external` ... external signal cut

### Conditions

Conditions are (currently) implemented as functions, located in the `gtl::condition` namespace.

Current implementation:

* `gtl::condition::comb` ... combination condition
* `gtl::condition::signal` ... signal condition for centrality and external signals

### Utilities

Generic implementations af functions and structs are located in the `gtl::utils` namespace.

Current implementation:

* `gtl::utils::math` ... constant expression preprocessor math functions
* `gtl::utils::range` ... range container template (minimum, maximum)
* `gtl::utils::signal_vector` ... signal vector template (access single bits of `ap_uint` vector)

## Test bench

Current implementation:

* `tb/algos_test.h/cpp` ... main automated test bench
* `tb/byte_vector.h` ... arbitrary integer emulation
* `tb/bytelify.h/cpp` ... arbitrary hex string to byte vector conversion
* `tb/ostream_utils.h/cpp` ... object string stream conversions
* `tb/test_vector.h/cpp` ... test vector file reader/parser
