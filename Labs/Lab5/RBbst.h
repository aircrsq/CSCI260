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
  node * insertNode(int k, string d, node *&n);
  node * finding(node *&n,int ,int );
  node * insert_case1(node *&n, node *&head);
  node * insert_case2(node *&, node *&);
  node * insert_case3(node *&, node *&);
  node * insert_case4(node *&, node *&);
  node * insert_case5(node *&, node *&);
  node * uncle(node *&);
  node * grandparent(node *&);
  node * rotate_left(node *, node *);
  node * rotate_right(node *, node *);
  node * Double_rotate_left(node *, node *);
  node * Double_rotate_right(node *, node *);
  string search(int, node *&n);
  void print(node *&n);
  void debugprint(node *&n);
  void PreOrdprint(node *&n);
  bool deleteElement(int, node* &);
  node * maximum_node(node *&);
  void delete_case1(node *&root, node *&t);
  void delete_case2(node *&root, node *&t);
  void delete_case3(node *&t, node *&n);
  void delete_case4(node *&t, node *&n);
  void delete_case5(node *&t, node *&n);
  void delete_case6(node *&t, node *&n);
  node * sibling(node *&n);
  void replace_node(node *&root, node *&n, node *&child);
  void verify_properties(node *&n);
  void verify_property_1(node *&n);
  void verify_property_2(node *&n);
  void verify_property_3(node *&n);
  void verify_property_4(node *&n);
  void verify_property_4_helper(node *&n, int black_count, int* path_black_count);
  int node_colour(node *n);
  void deallocate(node* &n);
  void swapElements(node* n, node* m);

  public:
  //Constructors
  RBbst() {
    Sentinel = new node;
    Sentinel->parent = Sentinel;
    Sentinel->left = Sentinel;
    Sentinel->right = Sentinel;
    Sentinel->key = -99999999;
    Sentinel->data = "Sentinel";
    Sentinel->colour = BLACK;
    root = Sentinel;
  }
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
    root = insertNode(key, data, root);
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
