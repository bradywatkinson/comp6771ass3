CC=g++
CFLAGS=-std=c++11 -Wall -Werror -O2 -DNDEBUG

All: test0

test0: test0.cpp Graph.h
	$(CC) $(CFLAGS) test0.cpp -o test0

clean:
	rm *.o
