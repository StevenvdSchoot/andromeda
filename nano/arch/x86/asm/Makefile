include ${INCLUDE}

IO=io.asm
IRQ=irq.asm
ISR=isr.asm
GDT=lgdt.asm
ASM=asm.asm

.PHONY: all
all: io.o irq.o isr.o lgdt.o asm.o

io.o: io.asm
	$(AS) $(ASFLAGS) $(FLAGS) $(IO)

irq.o: irq.asm
	$(AS) $(ASFLAGS) $(FLAGS) $(IRQ)

isr.o: isr.asm
	$(AS) $(ASFLAGS) $(FLAGS) $(ISR)

lgdt.o: lgdt.asm
	$(AS) $(ASFLAGS) $(FLAGS) $(GDT)

asm.o: asm.asm
	$(AS) $(ASFLAGS) $(FLAGS) $(ASM)

.PHONY: clean
clean:
	rm -fv *.o
