Playing around with Hardware Description Languages. Nothing too serious, just
taking a look how all of this works.

## How?

All simulation is done via [Verilator](https://www.veripool.org/verilator/) and
the results are displayable with [GTKWave](https://gtkwave.sourceforge.net/).
Make sure that you have both of these dependencies installed (and beware
openSUSE's weird default installation path for Verilator!).

Each design lives into its own file inside of `src`. Hence, for the `simple.vs`
design, you simply need to call:

``` sh
$ make wave.simple
```

This will verilate the SystemVerilog file, compile the resulting C++ code
together with its corresponding simulation from the `sim` directory, and launch
GTKWave for the resulting wave file.

After you are done with all of this, simply call `make clean` and go touch some
grass.

## License

Released under the [GPLv3+](http://www.gnu.org/licenses/gpl-3.0.txt), Copyright
(C) 2024-<i>Ω</i> Miquel Sabaté Solà.
