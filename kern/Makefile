include ${INCLUDE}

DEPS=sched.c
HEADERS=
TARGETS=kern.o

.PHONY: all
all: $(TARGETS)
	mv -v kern.o ../

$(TARGETS): $(DEPS) $(HEADERS)
	$(CC) $(CFLAGS) $(FLAGS) $(DEPS)
	$(LD) $(LDFLAGS) -o $(TARGETS) *.o

.PHONY: clean
clean:
	rm -fv *.o
