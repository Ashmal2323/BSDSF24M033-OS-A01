# Top-level Makefile: delegates the real build work to src/

.PHONY: all clean static

all:
	$(MAKE) -C src

static:
	$(MAKE) -C src static

clean:
	$(MAKE) -C src clean
