##
# By default everything is silent. If you want to change this behavior, simple
# assign V=1 when calling make.

V =
ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

##
# Paths and dependencies.

SRC=src
SIMDIR=sim
SIMOUTDIR=build
VERILATOR=verilator
GTKWAVE=gtkwave

##
# Actual make targets.

.PHONY: verilate
verilate: $(SIMOUTDIR)/simple.o

$(SIMOUTDIR)/%.o: $(SIMDIR)/%.cpp $(SRC)/%.sv
	$(E) "	VERILATE	" $*
	$(Q) $(VERILATOR) -Wall --cc -I$(SRC) --trace $*.sv --exe --Mdir $(SIMOUTDIR) --build -j $(shell nproc) $(SIMDIR)/$*.cpp >/dev/null

simulate.%: verilate
	$(Q) $(SIMOUTDIR)/V$*

wave.%: simulate.%
	$(Q) $(GTKWAVE) $*.vcd

.PHONY: clean
clean:
	$(Q) rm -rf build
	$(Q) rm -rf *.vcd

.PHONY: lint
lint: $(SRC)/*.sv
	$(VERILATOR) --lint-only -Wall $<
