include ${INCLUDE}

DEPS=math.c
TARGETS=maths.o
HEADERS=

.PHONY: all
all: $(TARGETS)
	mv -fv maths.o ../

$(TARGETS): $(DEPS) $(HEADERS)
	$(CC) $(CFLAGS) $(FLAGS) $(DEPS)
	$(LD) $(LDFLAGS) -o $(TARGETS) *.o

.PHONY: clean
clean:
	rm -v *.o
