include ${INCLUDE}

.PHONY: all
all: x86
	mv -fv arch.o ../

.PHONY: x86
x86:
	$(MAKE) $(MAKEEND) -C x86

.PHONY: clean
clean:
	$(MAKE) -C x86 clean
