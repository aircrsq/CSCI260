#/************************************************************************
# Design Unit  : Lab4

# File Name    : makefile

# Purpose      : makefile for Testapp for BST

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
# 1.0          DB      Sep 29  New version
#*************************************************************************/
# master Makefile for testapp program for bst

# Make targets:
#   make		-- creates testapp program
#   make testapp	-- creates testapp program
#   make clean		-- removes all .o files and the executable

testapp:	testapp.o bst.o
	g++ -o testapp testapp.o bst.o

testapp.o:	bst.h testapp.cpp
	g++ -c testapp.cpp

bst.o:	bst.h bst.cpp
	g++ -c bst.cpp
clean:
	rm -rf *o
	rm -rf testapp
