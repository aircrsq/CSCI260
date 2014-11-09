#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
//vector <std::list<int> > Adj;

int graph::file_read(char *fn){
  string line;
  ifstream myfile (fn);
  list <int> neighbors;
  int InputLines = 0;
  //if the input file is open
  if (myfile.is_open()){
    //get the first line
    getline(myfile,line);
    this->n = atoi(line.c_str());
    //read remainder of file until 99
    while ((getline(myfile,line)) && (line != "99")){
      //chop the line into separate words
      stringstream ss(line);
      string tmp;
      while(std::getline(ss, tmp, ' ')){
        if (tmp != " " && (atoi(tmp.c_str())) < n){
          //push onto neighbors
          neighbors.push_back(atoi(tmp.c_str()));
        }
      }
      neighbors.pop_front();
      //assign neighbors to Adj
      this->Adj.push_back(neighbors);
      //clear the neighbors
      neighbors.clear();
      InputLines++;
    }
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
  cout << n << endl;
  std::vector<std::list<int> >::iterator i;
  int c=0;
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
int graph::BreadthFirstTraversal(int v){
  //set up the visit aray
  bool *visited = new bool[n];
  for(int i = 0; i < n; i++){
    visited[i] = false;
  }
  //queue for BFS
  list<int> queue;
  //visit v
  visited[v] = true;
  //push v onto queue
  queue.push_back(v);
  //iterator for neighbors
  list<int>::iterator i;
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
}
