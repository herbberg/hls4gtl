# hls4gtl
Creating GTL with High Level Synthesis

### Usage

    $ git clone https://github.com/herbberg/hls4gtl.git

Open the project directory using Vivado HLS.

Default solution clock is 25ns.

### Implement a menu

Use ```distribute.py``` to generate a menu distribution/implementation.

  $ python utils/distribute.py sample.xml

The script creates a symbolic link ```current_dist``` in the projects root
directory pointing to the generated menu distribution. Use this path to include
the auto generated implementation headers into the design.
