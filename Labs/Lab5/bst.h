#ifndef BST
#define BST
/************************************************************************
 Design Unit  : Lab5

 File Name    : bst.h

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
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
using namespace std;

const int NO_NODE = 0;

class bst{
  private:
  enum colour { r, b };
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         enum colour colour;
  };//*node;
/*  struct NullNode {
         bst::node *right = NO_NODE;
         bst::node *left = NO_NODE;
         bst::node *parent = NO_NODE;
         string data = "N";
         int key = N; have to figure out how to convert?
         enum colour colour;
};  */
  struct rbtree {
    node root;
  };

  node* NullNode;
  // we maintain a pointer to the root of the tree
  node *root;

  // private, recursive routines
  // (used by the public methods)
  // see bst.cpp file for explanation
  void deallocate(node* &n);
  bool insert(int k, string d, node* &n);
  bool deleteElement(int k, node* &n);
  string search(int k, node* &n);
  bool Attach(int key, string data, node * &n, node * &c);
  bool AttachEqual(int key, string data, node * &n);
  bool leftjoin(int key, string data, node *&n);
  bool rightjoin(int key, string data, node *&n);
  node * FindVictim(int key, node *&n);
  node * LeftSuccessor(int key, node *&victim);
  node * RightSuccessor(int key, node *&victim);
  void TDK(node *&Vic, node *&Suc);
  void RCL(node *&SP, node *&SC);
  void RCR(node *&SP, node *&SC);
  void print(node *n);
  void debugprint(node *n);
  void PreOrdprint(node *n);
  void swapElements(node* n, node* m);
  node* grandparent(node *&n);
  node* sibling(node *&n);
  node* uncle(node *&n);
  void verify_property_1(node *&n);
  void verify_property_2(node *&root);
  void verify_property_4(node *&n);
  void verify_property_5(node *&root);
  void verify_property_5_helper(node *&n, int black_count, int* path_black_count);
  colour node_colour(node *&n);
  rbtree rbtree_create();
  node* new_node(void* k, void* v, colour n_colour, node left, node right); //verify input arguements
  node* lookup_node(rbtree t, void* key, compare_func compare); //Verify input arguements
  void rotate_left(rbtree t, node *&n);
  void rotate_right(rbtree t, node *&n);
  void replace_node(rbtree t, node oldn, node newn);
  void rbtree_insert(rbtree t, void* key, void* value, compare_func compare);
  void insert_case1(rbtree t, node *&n);
  void insert_case2(rbtree t, node *&n);
  void insert_case3(rbtree t, node *&n);
  void insert_case4(rbtree t, node *&n);
  void insert_case5(rbtree t, node *&n);
  void rbtree_delete(rbtree t, void* key, compare_func compare);
  node* maximum_node(node *&n);
  void delete_case1(rbtree t, node *&n);
  void delete_case2(rbtree t, node *&n);
  void delete_case3(rbtree t, node *&n);
  void delete_case4(rbtree t, node *&n);
  void delete_case5(rbtree t, node *&n);
  void delete_case6(rbtree t, node *&n);
  int compare_int(void* leftp, void* rightp);


  public:
    //Constructors
    bst() { root = NULL; }
    ~bst() { deallocate(root); }

    //prints tree in Inorder
    void display() {
      cout << endl;
      print(root);
    }

    //finds node k and returns the data associated with node
    void find(int k) {
      string SearchResult = search(k,root);
      cout << SearchResult;
    }

    //prints node key and pointer information
    void debug() { debugprint(root); }

    //prints node key and pointer information
    void PreOrd() { PreOrdprint(root); }

    //Inserts a node with key k and data d into the tree
    bool insert(int k, string d) {
      if (insert(k, d, root))
        return true;
      else return false;
    }

    //removes a node and its information from the tree
    bool deleteElement(int k) {
      if (deleteElement(k, root))
        return true;
      else return false;
    }
};

#endif
