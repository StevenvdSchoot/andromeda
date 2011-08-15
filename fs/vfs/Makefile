include ${INCLUDE}

TARGETS=fs.c

.PHONY: all
all: vfs.o
	mv -fv vfs.o ../

vfs.o: $(TARGETS)
	$(CC) $(TARGETS) $(FLAGS) $(CFLAGS)
	$(LD) -o vfs.o *.o $(LDFLAGS)
	
.PHONY: clean
clean:
	rm -fv *.o
