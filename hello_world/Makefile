CC=gcc
CFLAGS=-g
OBJ = hello_world.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

hello_world: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o hello_world
