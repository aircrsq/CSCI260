/************************************************************************
 Design Unit  : Lab8

 File Name    : graph.cpp

 Purpose      : source file for graph

 Note         :

 Limitations  : none known

 Errors       : none known

 Modules      :

 Dependences  : graph.h
		fstream
		stdlib.h
		string
		iostream
		sstream
		vector

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Nov 04  First implementation
 1.1          DB      Nov 10  Implement new version of BFS
*************************************************************************/
#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
//vector <std::list<int> > Adj;

int graph::file_read(char *fn){
//int line;
  string line;
  ifstream myfile (fn);
  int Vertex;
  list <int> neighbors;
  int InputLines = 0;
  //if the input file is open
  if (myfile.is_open()){
    //get the first line
    myfile >> Vertex;
    this->n = Vertex;
    //read remainder of file until 99
    while (InputLines < n /*&& (Vertex != 99)*/){
      myfile >> Vertex;
      while (Vertex < n){
        neighbors.push_back(Vertex);
        myfile >> Vertex;
      } 
      neighbors.pop_front();
      this->Adj.push_back(neighbors);
      neighbors.clear();
      cout << "Clear neighbors" << endl;
      InputLines++;
    }
    cout << "Close file" << endl; 
    myfile.close();
  }
  //file could not be opened
  else {
    cout << "File could not be opened" << endl;
  }
  //return the number of input lines
  return InputLines;
}
//add an edge
int graph::add_edge(int u, int v){
  Adj[u].push_back(v);
}
//remove an edge
int graph::remove_edge(int u, int v){
  Adj[u].remove(v);
}
//check if two vertices are adjacent
int graph::adjacent(int u, int v){
  std::list<int> li = Adj[u];
  for(std::list<int>::iterator iter = li.begin(); iter!= li.end(); ++iter){
    if (*iter = v){
      cout << u << " and " << v << " are adjacent" << endl;
    }
  }
}
//debug print the graph
bool graph::print_graph(){
  std::vector<std::list<int> >::iterator i;
  int c=0;
  cout << n << endl;
  for (std::vector<std::list<int> >::iterator i=Adj.begin(); i !=Adj.end(); ++i){
    cout<< c <<": ";
    std::list<int> li = *i;
    for(std::list<int>::iterator iter = li.begin(); iter!= li.end(); ++iter){
      cout<<*iter<<" ";
    }
    cout<<endl;
    c++;
  }
  return 1;
}
//print the adjacency for vertex
bool graph::print_vertex(int v){
    std::list<int> li = Adj[v];
    cout << v << " : ";
    for(std::list<int>::iterator iter = li.begin(); iter!= li.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
  return 1;
}
//BFS from vertex
void graph::BreadthFirstTraversal(int v){
  cout << "BFS on " << v << endl;
  //queue for BFS
  list<int> queue;
  //iterator for neighbors
  list<int>::iterator i;
  //set up the visit aray
  bool *visited = new bool[n];
  for(int i = 0; i < n; i++){
    visited[i] = false;
  }
  //visit v
  visited[v] = true;
  //push v onto queue
  queue.push_back(v);
  //while the queue is not empty
  while(!queue.empty()){
    //get the front of queue
    v = queue.front();
    //display the vertex
    cout << v << " ";
    //pop off the vertex
    queue.pop_front();
    //check the neighbors
    for(i = Adj[v].begin(); i != Adj[v].end(); ++i){
      //if neighbor has not been visited
      if(!visited[*i]){
        //visit neighbor
        visited[*i] = true;
        //push neighbor into queue
        queue.push_back(*i);
      }
    }
  }
  cout << endl;
  //DepthFirstSearch(v);
}
// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
void graph::DepthFirstSearch(int v){
  cout << "DFS on " << v << endl;
  // Mark all the vertices as not visited
  bool *visited = new bool[v];
  for(int i = 0; i < v; i++)
    visited[i] = false;
  // Call the recursive helper function to print DFS traversal
  DFShelp(v, visited);
}

void graph::DFShelp(int v, bool visited[]){
  // Mark the current node as visited and print it
  visited[v] = true;
  cout << v << " ";
  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for(i = Adj[v].begin(); i != Adj[v].end(); ++i)
    if(!visited[*i])
      DFShelp(*i, visited);
}

void graph::BreadthFirstTraversal(int v, void (*f) (int)){
  cout << "BFS2 on " << v << endl;
  //queue for BFS
  list<int> queue2;
  //iterator for neighbors
  list<int>::iterator i;
  //set up the visit aray
  bool *visited = new bool[n];
  for(int i = 0; i < n; i++){
    visited[i] = false;
  }
  //visit v
  visited[v] = true;
  f(v);
  //push v onto queue
  queue2.push_back(v);
  //while the queue is not empty
  while(!queue2.empty()){
    //get the front of queue
    v = queue2.front();
    //pop off the vertex
    queue2.pop_front();
    //check the neighbors
    for(i = Adj[v].begin(); i != Adj[v].end(); ++i){
      //if neighbor has not been visited
      if(!visited[*i]){
        //visit neighbor
        visited[*i] = true;
        f(*i);
        //push neighbor into queue
        queue2.push_back(*i);
      }
    }
  }
  cout << endl;
}

