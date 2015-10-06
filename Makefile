CC=g++
CFLAGS=-std=c++11 -Wall -Werror -O -DNDEBUG

iteratorTestNode: tests/iteratorTestNode Graph.h
	  $(CC) $(CFLAGS) tests/iteratorTestNode.cpp -o iteratorTestNode

mergeReplace: tests/mergeReplace Graph.h
	  $(CC) $(CFLAGS) tests/mergeReplace.cpp -o mergeReplace

iteratorTestEdge: tests/iteratorTestEdge.cpp Graph.h
	  $(CC) $(CFLAGS) tests/iteratorTestEdge.cpp -o iteratorTestEdge

deletion: tests/deletion.cpp Graph.h
	  $(CC) $(CFLAGS) tests/deletion.cpp -o deletion

iteratorTest: tests/iteratorTest.cpp Graph.h
	  $(CC) $(CFLAGS) tests/iteratorTest.cpp -o iteratorTest

postIncrement: tests/postIncrement.cpp Graph.h
	  $(CC) $(CFLAGS) tests/postIncrement.cpp -o postIncrement

sameEdges: tests/sameEdges.cpp Graph.h
	  $(CC) $(CFLAGS) tests/sameEdges.cpp -o sameEdges

addDeleteEdge: tests/addDeleteEdge.cpp Graph.h
	  $(CC) $(CFLAGS) tests/addDeleteEdge.cpp -o addDeleteEdge

iteratorMemory: tests/iteratorMemory.cpp Graph.h
	  $(CC) $(CFLAGS) tests/iteratorMemory.cpp -o iteratorMemory	

addDelete: tests/addDelete.cpp Graph.h
	  $(CC) $(CFLAGS) tests/addDelete.cpp -o addDelete

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

test13: tests/test13.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test13.cpp -o test13

test14: tests/test14.cpp Graph.h
	  $(CC) $(CFLAGS) tests/test14.cpp -o test14

clean:
	rm test0 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14
