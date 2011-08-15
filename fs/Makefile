include ${INCLUDE}

TARGETS=io.c

.PHONY: all
all: vfs.o fs.o
	mv -v vfs.o ../

vfs.o:
	$(MAKE) -C vfs $(MAKEEND)

fs.o: $(TARGETS)
	$(CC) $(TARGETS) $(FLAGS) $(CFLAGS)
	$(LD) -o fs.o *.o $(LDFLAGS)
	
.PHONY: clean
clean:
	rm -fv *.o
	$(MAKE) -C vfs/ clean
