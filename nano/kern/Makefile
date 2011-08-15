include ${INCLUDE}

ELF=elf.c exec.c
TIMER=timer.c

.PHONY: all
all: kern.o
	mv -fv kern.o ../

kern.o: load.o timer.o
	$(LD) $(LDFLAGS) *.o -o kern.o
load.o: $(ELF)
	$(CC) $(CFLAGS) $(FLAGS) $(ELF)

timer.o: $(TIMER)
	$(CC) $(CFLAGS) $(FLAGS) $(TIMER)

.PHONY: clean
clean:
	rm -fv *.o
