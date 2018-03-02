CC=g++
CFLAGS=-Wall -std=c++11 -O3
INCLUDE = -I .
LINK = -L .
Files = main.cpp my_bitwise.cpp Node.cpp NodeTree.cpp Stack.cpp Table.cpp Table_stream.cpp Tree.cpp tree_constructor_four.cpp tree_constructor_three.cpp tree_constructor_two.cpp tree_constructor_one.cpp Vertex.cpp

all:
	${CC} ${Files} -o huffman ${CFLAGS} ${INCLUDE} ${LINK}