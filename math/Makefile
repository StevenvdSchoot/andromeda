include ${INCLUDE}

DEPS=math.c
TARGETS=maths.o
HEADERS=

.PHONY: all
all: $(TARGETS)
	mv -v maths.o ../

$(TARGETS): $(DEPS) $(HEADERS)
	$(CC) $(CFLAGS) $(FLAGS) $(DEPS)
	$(LD) $(LDFLAGS) -o $(TARGETS) *.o

.PHONY: clean
clean:
	rm -fv *.o
