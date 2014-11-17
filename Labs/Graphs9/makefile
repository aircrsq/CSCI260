#/************************************************************************
# Design Unit  : Lab9

# File Name    : makefile

# Purpose      : makefile for Testapp for graph

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
# 1.0          DB      Nov 04  New version
#*************************************************************************/
# master Makefile for testapp program for bst

# Make targets:
#   make			-- creates testapp program
#   make testapp	-- creates testapp program
#   make clean		-- removes all .o files and the executable

testapp:	testapp.o graph.o
	g++ -o testapp testapp.o graph.o

testapp.o:	graph.h testapp.cpp
	g++ -c testapp.cpp

graph.o:	graph.h graph.cpp
	g++ -c graph.cpp
clean:
	rm -rf *o
	rm -rf testapp
