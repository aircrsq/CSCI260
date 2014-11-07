/****************************************************************
/*            graph.h
/*            by Gara Pruesse
/*            Oct 5 2009
/*
/*            class that reads a graph in from a file
/*            builds graph, provides graph access routines
/*
/*********************************************************************/
#include <string>
#include <fstream>
#include <iostream>
#include <values.h>
#include <vector>   // STL vector, for adjacency list; ability to iterate

using namespace std;

const int NO_EDGE=0;
const int white=0;
const int grey=1;
const int black=2;

class graph {
   private:
      int n;
      int default_nonedge;
      vector<int> *Adj;  // array of neighbour-vector
                                // all subsequent entries are names of neighbou


   public:
        graph();
        graph(int num) {n=num;}
	int graph_read(char *fn);
	~graph();
	int num_vertices() { return n; }
	int add_edge(int u, int v);
	int remove_edge(int u, int v);
	int adjacent(int u, int v);
	int first_neighbour(int v);
	int next_neighbour(int v);
	bool print_graph();
	bool print_vertex(int v);
	int BreadthFirstTraversal(int v);
};



