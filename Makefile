VPATH = .:src
CFLAGS=-g

firstlisp: .aux/out/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.aux/out/main.o: main.o
	mv $^ $@
