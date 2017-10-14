all: test9

test9: test9.cpp BSTree.cpp
	g++ -Wall -o test9 test9.cpp BSTree.cpp -std=c++98

BSTree.cpp: BSTree.h
