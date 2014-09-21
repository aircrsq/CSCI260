#/************************************************************************
# Design Unit  : Lab2

# File Name    : makefile

# Purpose      : makefile for Trominos

# Note         :

# Limitations  :

# Errors       : none known

# Modules      :

# Dependences  : none

# Author       : David Burneau, Vancouver Island University

# System       : G++ (Linux)

#------------------------------------------------------------------
# Revision List
# Version      Author  Date    Changes
# 1.0          DB      Sep 19  New version
#*************************************************************************/
# master Makefile for Trominos program

# Make targets:
#
#   make Trominos	-- creates Trominos program
#   make clean		-- removes all .o files and the executable

Trominos: main.o gameboard.o
	g++ -o Trominos main.o gameboard.o

main.o: gameboard.h main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o
	rm -rf Trominos
