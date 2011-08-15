include ${INCLUDE}

DEPS=VGA.c graphics.c text.c
TARGETS=vga.o
HEADERS=Include/VGA.h Include/graphics.h Include/text.h

.PHONY: all
all: $(TARGETS)
	mv vga.o ../graphics.o;

$(TARGETS): $(DEPS) $(HEADERS)
	$(CC) $(CFLAGS) $(FLAGS) $(DEPS)
	$(LD) $(LDFLAGS) -o $(TARGETS) *.o

.PHONY: clean
clean:
	rm -fv *.o
