#ifndef RBBST
#define RBBST
/************************************************************************
 Design Unit  : Lab5

 File Name    : RBbst.h

 Purpose      : Header file for bst

 Note         :

 Limitations  : none known

 Errors       : none known

 Modules      :

 Dependences  : none

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 06  New version Original code provide by
                              Professor Gara Pruesse
*************************************************************************/
#include<string>
#include<iostream>

using namespace std;

//Define Black as 1 and Red as 0
#define BLACK 1
#define RED 0

class RBbst{
  private:
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         int colour;
  };
  // we maintain a pointer to the root of the tree
  node * root;
  node * Sentinel;

  // private, recursive routines (used by the public methods)
  // see RBbst.cpp file for explanation
  void insertNode(int, string, node *&);
  node * Find(node *&,int ,int );
  void insert_case1(node *&, node *&);
  void insert_case2(node *&, node *&);
  void insert_case3(node *&, node *&);
  void insert_case4(node *&, node *&);
  void insert_case5(node *&, node *&);
  node * uncle(node *&);
  node * grandparent(node *&);
  node * sibling(node *&);
  void rotate_left(node *, node *);
  void rotate_right(node *, node *);
  string search(int, node *&);
  void print(node *&);
  void debugprint(node *&);
  void PreOrdprint(node *&);
  bool deleteElement(int, node*&);
  node * maximum_node(node *&);
  void delete_case1(node *&, node *&);
  void delete_case2(node *&, node *&);
  void delete_case3(node *&, node *&);
  void delete_case4(node *&, node *&);
  void delete_case5(node *&, node *&);
  void delete_case6(node *&, node *&);
  int node_colour(node *);
  void deallocate(node *&);
  void swapElements(node*& , node*&);

  public:
  //Constructor
  RBbst() {
    //Make a new node initialized as a sentinel
    //and have it assigned to root
    Sentinel = new node;
    Sentinel->parent = Sentinel;
    Sentinel->left = Sentinel;
    Sentinel->right = Sentinel;
    Sentinel->key = -99999999;
    Sentinel->data = "Sentinel";
    Sentinel->colour = BLACK;
    root = Sentinel;
  }
  //Destructor
  ~RBbst() { deallocate(root); }

  //prints tree in Inorder
  void display() {
    cout << endl;
    print(root);
  }

  //prints node key and pointer information
  void debug(){
    cout << endl;
    debugprint(root);
  }

  //prints node key and pointer information
  void PreOrd(){
    PreOrdprint(root);
  }

  //finds node k and returns the data associated with node
  void find(int k) {
    string SearchResult = search(k,root);
    cout << SearchResult;
  }

  //Inserts a node with key k and data d into the tree
  bool insert(int key, string data) {
    insertNode(key, data, root);
    return true;
  }

  //removes a node and its information from the tree
  bool deleteElement(int k) {
    if (deleteElement(k, root))
      return true;
    else return false;
  }
};
#endif
