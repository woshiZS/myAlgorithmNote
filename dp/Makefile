CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: test

test: spaceCutDp.o 
	$(CC) $(CFLAGS) -o test -g test.c spaceCutDp.o

spaceCutDp.o: spaceCutDp.c
	$(CC) $(CFLAGS) -g -c spaceCutDp.c

clean:
	rm -f test *.o

scan-build: clean
	scan-build make

