#/************************************************************************
# Design Unit  : Lab5

# File Name    : makefile

# Purpose      : makefile for Testapp for RBbst

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
# 1.0          DB      Oct 06  New version
#*************************************************************************/
# master Makefile for testapp program for bst

# Make targets:
#   make		-- creates testapp program
#   make testapp	-- creates testapp program
#   make clean		-- removes all .o files and the executable

testapp:	testapp.o RedBlackTree.o
	g++ -o testapp testapp.o RedBlackTree.o

testapp.o:	RedBlackTree.h main.cpp
	g++ -c main.cpp

RedBlackTree.o:	RedBlackTree.h RedBlackTree.cpp
	g++ -c RedBlackTree.cpp
clean:
	rm -rf *o
	rm -rf testapp
