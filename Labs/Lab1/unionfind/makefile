# master Makefile for uinonfind program

# Make targets:
#
#   make TestappQF	-- creates TestappQF program
#   make testappQU	-- creates TestappQF program
#   make testappQUPCR -- creates TestappQF program
#   make clean		-- removes all .o files
#   make gdb		-- invokes the gdb debugger on Testapp

# For the Testapp target, different versions may be created by supplying
# different settings for the CFLAGS parameter.  Possible versions are:
#
# 1. For a debugging version (usable with the gdb debuggers)
#    while developing the code (this is the default):
#	make 'CFLAGS=-g' Testapp
#
# 2. For a version of Testapp that generates execution profiles:
#	make 'CFLAGS=-pg' Testapp
#
# 3. For an (optimized) production version of the program:
#	make 'CFLAGS=-O' Testapp
#
# NOTE:	If you want to switch from one version of Testapp to another (e.g.
#	after having produced the debugging version, you now want a
#	profiling version), you must execute
#		make clean
#	first.

# List of directories holding code and tests for each module
MODULES = Testapp unionfindQF unionfindQU unionfindQUPRC

# Default compilation flags for IBM xlc compiler
CFLAGS = -g

# Directory holding all the .h files
INC = include

XCFLAGS = -I$(INC)  ## extra C flags

CC = g++ $(XCFLAGS)

IMPINC = $(INC)/unionfind.h

IMPOBJ = Testapp/Testapp.o unionfindQF/unionfindQF.o unionfindQU/unionfindQU.o \
	unionfindQUPRC/unionfindQUPRC.o

TestappQF:
	Testapp.o unionfindQF.o
	g++ -o TestappQF Testapp.o unionfindQF.o
TestappQU:
	Testapp.o unionfindQU.o
	g++ -o TestappQU Testapp.o unionfindQU.o
TestappQUPCR:
	Testapp.o unionfindQUPRC.o
	g++ -o TestappQU Testapp.o unionfindQUPRC.o
Testapp.o: unionfind.h Testapp.cpp
	g++ - Testapp.cpp

gdb:	Testapp
	gdb -d Testapp -d unionfindQF -d unionfindQU -d unionfindQUPRC unionfind

main.o: $(INC)/unionfind.h $(IMPINC)
	$(CC) -c $(CFLAGS) Testapp.c

clean:
	for m in $(MODULES); do \
		( cd $$m; rm -f *.o ) \
	done
	rm -f Testapp core mon.out gmon.out *.o

gcov:
	for m in $(MODULES); do \
		( cd $$m; $(MAKE) gcov; ) \
	done
