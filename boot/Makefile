include ${INCLUDE}

.PHONY: all
all: coreboot.o
	mv -v coreboot.o ../

coreboot.o: init.o boot.o 
	$(LD) $(LDFLAGS) *.o -o coreboot.o

init.o: init.c
	$(CC) $(CFLAGS) $(FLAGS) init.c

boot.o: boot.asm
	$(AS) $(ASFLAGS) $(FLAGS) boot.asm

.PHONY: clean
clean:
	#rm -v *.o
