include ${INCLUDE}

DEPS=beep.c
TARGETS=system\ beep.o
HEADERS=Include/beep.h

.PHONY: all
all: $(TARGETS)
	mv -fv system\ beep.o ../;

$(TARGETS): $(DEPS) $(HEADERS)
	$(CC) $(CFLAGS) $(FLAGS) $(DEPS)
	$(LD) $(LDFLAGS) -o $(TARGETS) *.o

.PHONY: clean
clean:
	rm -fv *.o
