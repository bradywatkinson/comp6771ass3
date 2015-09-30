CC=g++
CFLAGS=-std=c++11 -Wall -Werror -O2 -DNDEBUG

all: test0 test1 test2 test3 test4 test5 test6

test0: test0.cpp Graph.h
	  $(CC) $(CFLAGS) test0.cpp -o test0

test1: tests/test1.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test1.cpp -o test1
	
test2: tests/test2.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test2.cpp -o test2
	
test3: tests/test3.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test3.cpp -o test3
	
test4: tests/test4.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test4.cpp -o test4
	
test5: tests/test5.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test5.cpp -o test5
	
test6: tests/test6.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test6.cpp -o test6
	
test7: tests/test7.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test7.cpp -o test7
	
test8: tests/test8.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test8.cpp -o test8
	
test9: tests/test9.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test9.cpp -o test9
	
test10: tests/test10.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test10.cpp -o test10
	
test11: tests/test11.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test11.cpp -o test11
	
test12: tests/test12.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test12.cpp -o test12

clean:
	rm test0 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12
