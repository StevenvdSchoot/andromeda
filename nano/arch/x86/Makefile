include ${INCLUDE}

INTERRUPTS=interrupts/APIC.c interrupts/IDT.c interrupts/irq.c interrupts/isr.c interrupts/PIC.c
MM=mm/GDT.c

.PHONY: all
all: arch.o
	mv -fv arch.o ../

arch.o: $(INTERRUPTS) $(MM)
	$(CC) $(CFLAGS) $(FLAGS) */*.c
	$(MAKE) -C asm $(MAKEEND)
	$(LD) -o arch.o asm/*.o *.o $(LDFLAGS)

.PHONY: clean
clean:
	$(MAKE) -C asm clean
	rm -fv *.o
