# hls4gtl

Creating GTL with High Level Synthesis

### Usage

    $ git clone https://github.com/herbberg/hls4gtl.git
    $ git checkout <branch/tag>
    $ python manage.py init </path/to/menu/dist> <module_id>
    $ make

Use ```manage.py``` to handle linked module distribution (append ```--help``` for more information):

    $ python manage.py init|status|clean [args...]

Run individual makefile targets:

    $ make csim|csynth|cosim|export|clean

Default solution clock is 24ns.

### Implement a menu

Use ```distribute.py``` to generate a menu distribution/implementation.

    $ python utils/distribute.py L1Menu_sample.xml

The script creates a symbolic link ```current_dist``` in the projects root
directory pointing to the generated menu distribution. Use this path to include
the auto generated implementation headers into the design.

Generated directory structure:

    hls4gtl
    ├── current_dist -> dist/L1Menu_sample-d1
    └── dist
        └── L1Menu_sample-d1
            ├── hls
            │   └── module_0
            │       └── src
            │           └── impl
            │               ├── menu.hxx
            │               ├── conditions.hxx
            │               ├── cuts.hxx
            │               └── seeds.hxx
            ├── testvector
            ├── vhdl
            │   └── module_0
            │       └── src
            │           └── constants_pkg.vhd
            │   
            └── xml
                └── L1Menu_sample-d1.xml



### Simulate with test vector

Append a test vector filename to the csim argument list (argv).
