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

TestappQF: Testapp.o unionfindQF.o
	g++ -o TestappQF Testapp.o unionfindQF.o

TestappQU: Testapp.o unionfindQU.o
	g++ -o TestappQU Testapp.o unionfindQU.o

TestappQUPCR: Testapp.o unionfindQUPRC.o
	g++ -o TestappQUPCR Testapp.o unionfindQUPRC.o

Testapp.o: unionfind.h Testapp.cpp
	g++ -c Testapp.cpp

unionfindQF.o: unionfindQF.cpp
	g++ -c unionfindQF.cpp

unionfindQU.o: unionfindQU.cpp
	g++ -c unionfindQU.cpp

unionfindQUPRC.o: unionfindQUPRC.cpp
	g++ -c unionfindQUPRC.cpp

clean:
	rm -rf *o
	rm -rf TestappQ*
