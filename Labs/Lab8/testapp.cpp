/************************************************************************
 Design Unit  : Lab8

 File Name    : testapp.cpp

 Purpose      : Header file for graph

 Note         : Minimum modification

 Limitations  : none known

 Errors       : none known

 Modules      :

 Dependences  : graph.h
		iostream

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Nov 10  New version Original code provide by
                              Professor Gara Pruesse
*************************************************************************/
#include "graph.h"
#include <iostream>

char getcommand();
void printmenu();
bool processcommand(char cmd, graph &G);
void print_v(int v);

int main(){
   graph G;
   printmenu();
   char cmd = getcommand();
   while (processcommand(cmd, G)) {
      cout << endl;
      cmd = getcommand();
   }
   return 0;
}

char getcommand(){
   cout << "Enter your command choice (F, A, R, L, S, D, P, H, Q)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'F':
      case 'A':
      case 'R':
      case 'L':
      case 'T':
      case 'S':
      case 'D':
      case 'P':
      case 'H':
      case 'Q': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu(){
   cout << "Enter F to read a graph from a file," << endl;
   cout << "   or A to add an edge," << endl;
   cout << "   or R to remove an edge," << endl;
   cout << "   or L to list the neighbours of a vertex," << endl;
   cout << "   or T to initial BFS search the graph from a vertex," << endl;
   cout << "   or S to search the graph from a vertex," << endl;
   cout << "   or D to for debug data display," << endl;
   cout << "   or P to print Vertex display," << endl;
   cout << "   or H for help," << endl;
   cout << "   or Q to quit." << endl;
}

bool processcommand(char cmd, graph &G){
   int d; int x;
   int s;
   char fn[80];
   switch (cmd) {
     //Complete Read a graph from a file
     case 'F': cout << "File to read: ";
	   cin >> fn;
	   //call read function with filename
	   G.graph_read(fn);
         break;
     case 'A':
       int FirstAdd, SecondAdd;
       cout << "Enter first vertex ";
	   cin >> FirstAdd;
	   cout << "Enter second vertex ";
	   cin >> SecondAdd;
	   //call Add edge function with two vertices
	   G.add_edge(FirstAdd, SecondAdd);
         break;
     case 'R':
       int FirstRemove, SecondRemove;
       cout << "Enter first vertex ";
	   cin >> FirstRemove;
	   cout << "Enter second vertex ";
	   cin >> SecondRemove;
	   //call Add edge function with two vertices
	   G.remove_edge(FirstRemove, SecondRemove);
         break;
     case 'L': cout << "Not developed in this version" << endl;
         break;
     //Search the graph from a vertex
     case 'T': cout << "Vertex number to search from: ";
		cin >> s;
		if (s<0 || s>=G.num_vertices())
			cout << "Error, out of range.\n";
		else
			G.BreadthFirstTraversal(s);
                break;
     //Search the graph from a vertex
     case 'S': cout << "Vertex number to search from: ";
		cin >> s;
		if (s<0 || s>=G.num_vertices())
			cout << "Error, out of range.\n";
		else
			G.BreadthFirstTraversal(s, print_v(s));
                break;
      //Complete Debug data display
      case 'D': G.print_graph();
                break;
      //Complete Debug data display
      case 'P': cout << "Which vertex? ";
                cin >> s;
                G.print_vertex(s);
                break;
      //help
      case 'H': printmenu();
                break;
      default:  return false;
   }
   return true;
}
void print_v(int v){
  cout << v << " ";
}
