# Top-level Makefile: delegates the real build work to src/
# This is the "recursive make" pattern.

.PHONY: all clean

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
