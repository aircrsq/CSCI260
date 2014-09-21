# master Makefile for unionfind program

# Make targets:
#
#   make TestappQF	-- creates TestappQF program
#   make testappQU	-- creates TestappQF program
#   make testappQUPCR -- creates TestappQF program
#   make clean		-- removes all .o files
#   make gdb		-- invokes the gdb debugger on Testapp

#Test: Testapp.cpp unionfind.h unionfindQF.cpp
#	g++ -o Testapp Testapp.cpp unionfindQF.cpp

Trominos: main.o gameboard.o
	g++ -o Trominos main.o gameboard.o

main.o: gameboard.h main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o
	rm -rf Trominos
