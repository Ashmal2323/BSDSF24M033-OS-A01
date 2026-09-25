# Top-level Makefile: delegates the real build work to src/

.PHONY: all clean static dynamic

all:
	$(MAKE) -C src

static:
	$(MAKE) -C src static

dynamic:
	$(MAKE) -C src dynamic

clean:
	$(MAKE) -C src clean
