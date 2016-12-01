CC=gcc
BUILDLIBS=-L/usr/lib -lnetsnmp -lm
BUILDAGENTLIBS=-L/usr/lib -lnetsnmpmibs -ldl -lnetsnmpagent -Wl,-E -lnetsnmp -lm
CFLAGS=-g -I. -fno-strict-aliasing -g -O2 -Ulinux -Dlinux=linux -D_REENTRANT -D_GNU_SOURCE -DDEBIAN -fwrapv -fno-strict-aliasing -pipe -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -I/usr/lib/x86_64-linux-gnu/perl/5.20/CORE -I. -I/usr/include
OBJ = hello_world.o
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

hello_world: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -L/usr/lib -lnetsnmpmibs -ldl -lnetsnmpagent -Wl,-E -lnetsnmp -lm

clean:
	rm -f *.o hello_world
