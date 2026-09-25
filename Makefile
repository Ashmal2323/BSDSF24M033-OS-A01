# Top-level Makefile: delegates the real build work to src/

.PHONY: all clean static dynamic install

all:
	$(MAKE) -C src

static:
	$(MAKE) -C src static

dynamic:
	$(MAKE) -C src dynamic

install:
	$(MAKE) -C src install

clean:
	$(MAKE) -C src clean
