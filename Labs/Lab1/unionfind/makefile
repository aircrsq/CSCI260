# master Makefile for uinonfind program

# Make targets:
#
#   make TestappQF	-- creates TestappQF program
#   make testappQU	-- creates TestappQF program
#   make testappQUPCR -- creates TestappQF program
#   make clean		-- removes all .o files
#   make gdb		-- invokes the gdb debugger on Testapp

  # the compiler: gcc for C program, define as g++ for C++
     #CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
     #CFLAGS  = -g -Wall

  # the build target executable:
     #TARGET = myprog

     #all: $(TARGET)

     #$(TARGET): $(TARGET).c
	 #$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

     #clean:
  	 #$(RM) $(TARGET)


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
