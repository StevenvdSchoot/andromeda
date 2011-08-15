include ${INCLUDE}

TARGETS=alloc.c heap.c map.c memory.c paging.c test.c

.PHONY: all
all: mm.o
	mv -fv mm.o ../

mm.o: $(TARGETS)
	$(CC) $(TARGETS) $(FLAGS) $(CFLAGS)
	$(LD) -o mm.o *.o $(LDFLAGS)
	
.PHONY: clean
clean:
	rm -fv *.o
