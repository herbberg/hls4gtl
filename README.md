# hls4gtl

Creating GTL with High Level Synthesis

### Usage

    $ git clone https://github.com/herbberg/hls4gtl.git

Open the project directory using Vivado HLS.

Default solution clock is 25ns.

### Implement a menu

Use ```distribute.py``` to generate a menu distribution/implementation.

    $ python utils/distribute.py L1Menu_sample.xml

The script creates a symbolic link ```current_dist``` in the projects root
directory pointing to the generated menu distribution. Use this path to include
the auto generated implementation headers into the design.

Generated directory structure:

    hls4gtl
    ├── current_dist -> dist/L1Menu_sample
    └── dist
        ├── L1Menu_sample
        │   ├── hls
        │   │   ├── module_0
        │   │   │   └── src
        │   │   │       └── impl
        │   │   │           ├── .hxx
        │   │   │           ├── conditions.hxx
        │   │   │           ├── cuts.hxx
        │   │   │           └── seeds.hxx
        │   │   └── module_...
        │   └── vhdl
        │       ├── module_0
        │       │   └── src
        │       │       └── ugt_constants.vhd
        │       └── module_...
        └── L1Menu_...

### Run test bench with test vector

Assign a test vector path/filename to the csim argument list (argv).
