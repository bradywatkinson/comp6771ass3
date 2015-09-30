CC=g++
CFLAGS=-std=c++11 -Wall -Werror -O2 -DNDEBUG

all: test0 test1 test2

test2: tests/test2.cpp Graph.h
	$(CC) $(CFLAGS) tests/test2.cpp -o test2

test1: tests/test1.cpp Graph.h
	$(CC) $(CFLAGS) tests/test1.cpp -o test1

test0: tests/test0.cpp Graph.h
	$(CC) $(CFLAGS) tests/test0.cpp -o test0

clean:
	rm test0 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12