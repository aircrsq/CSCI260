#ifndef GRAPH
#define GRAPH
/****************************************************************
/*            graph.h
/*            by Gara Pruesse
/*            Oct 5 2009
/*
/*            class that reads a graph in from a file
/*            builds graph, provides graph access routines
/*
/*********************************************************************/
/************************************************************************
 Design Unit  : Lab9

 File Name    : graph.h

 Purpose      : Header file for graph

 Note         :

 Limitations  : none known

 Errors       : none known

 Modules      :

 Dependences  : string
		fstream
		iostream
		values.h
		vector
		list

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Nov 04  New version Original code provide by
                              Professor Gara Pruesse
 1.1          DB      Nov 10 Implement new version of BFS
*************************************************************************/
#include <string>
#include <fstream>
#include <iostream>
#include <values.h>
#include <vector> // STL vector, for adjacency list; ability to iterate
#include <list>

using namespace std;

const int NO_EDGE=0;
const int white=0;
const int grey=1;
const int black=2;

class graph {
   private:
      int n;
      int default_nonedge;
      vector <std::list<int> > Adj;
      int file_read(char *fn);  //Done
      // array of neighbour-vector
      // all subsequent entries are names of neighbou
   public:
    graph(){
      //make a new vector of lists
      std::vector <std::list<int> > Adj;
    }
    graph(int num) {
      n=num;
      //make a new vector of n lists
      std::vector <std::list<int> > Adj(n);
    }
	~graph(){
//	  delete &Adj;
	}
    int graph_read(char *fn){n = file_read(fn);};
	int num_vertices() { return n; };
	int add_edge(int u, int v);
	int remove_edge(int u, int v);
	int adjacent(int u, int v);
	int first_neighbour(int v);
	int next_neighbour(int v);
	bool print_graph();
	bool print_vertex(int v);
	void BreadthFirstTraversal(int v);
    void DepthFirstSearch(int v);
    void BreadthFirstTraversal(int v, void (*f) (int));
    void DFShelp(int v, bool visited[]);
};
#endif