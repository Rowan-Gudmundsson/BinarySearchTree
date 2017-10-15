all: test9 BSTree
	g++ -o test9 BSTree.o test9.o

test9: test9.cpp
	g++ -c test9.cpp

BSTree: BSTree.cpp BSTree.h
	g++ -c BSTree.cpp

clean: rm *.o
