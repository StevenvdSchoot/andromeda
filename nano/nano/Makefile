include ${INCLUDE}

.PHONY: all
all: kmain.o boot.o map.o
	mv -fv *.o ../

map.o:
	$(CC) $(CFLAGS) $(FLAGS) map.c

kmain.o: kmain.c
	$(CC) $(CFLAGS) $(FLAGS) kmain.c

boot.o: boot.asm
	$(AS) $(ASFLAGS) $(FLAGS) boot.asm

.PHONY: clean
clean:
	#rm -fv *.o
