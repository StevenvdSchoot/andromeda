include ${INCLUDE}

TARGETS=heap.c paging.c

.PHONY: all
all: coremm.o
	mv -v coremm.o ../

coremm.o: $(TARGETS)
	$(CC) $(TARGETS) $(FLAGS) $(CFLAGS)
	$(LD) -o coremm.o *.o $(LDFLAGS)
	
.PHONY: clean
clean:
	rm -fv *.o
