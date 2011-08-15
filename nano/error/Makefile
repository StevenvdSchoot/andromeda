include ${INCLUDE}

.PHONY: all
all: panic.o
	mv -fv panic.o ../

panic.o: panic.c
	$(CC) $(CFLAGS) $(FLAGS) panic.c

.PHONY: clean
clean:
	rm -fv *.o
