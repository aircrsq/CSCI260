
testapp:	testapp.o bst.o
	g++ -o testapp testapp.o bst.o

testapp.o:	bst.h testapp.cpp
	g++ -c testapp.cpp

bst.o:	bst.h bst.cpp
	g++ -c bst.cpp

