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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<string>
#include<iostream>

using namespace std;
#define BLACK 1
#define RED 0
const int NO_NODE = 0;

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

  // private, recursive routines (used by the public methods)
  // see RBbst.cpp file for explanation
    node * insert(int k, string d, node *&n);
    node * finding(node*& ,int ,int );
    node * insert_case1(node *&n, node *&head);
    node * insert_case2(node *&, node *&);
    node * insert_case3(node *&, node *&);
    node * insert_case4(node *&, node *&);
    node * insert_case5(node *&, node *&);
    node * uncle(node *&);
    node * grandparent(node *&);
    node * rotate_left(node *&, node *&);
    node * rotate_right(node *&, node *&);
    string search(int, node *&);
    void print(node *&);
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
    void verify_property_2(node *&root);
    void verify_property_3(node *&n);
    void verify_property_4(node *&root);
    void verify_property_4_helper(node *&n, int black_count, int* path_black_count);
    int node_colour(node *&n);
    void deallocate(node* &n);
    void print(node *n);
    void PreOrdprint(root);
/*
node* insertion( node*,int );
void inorder(node* );

*/

  public:
    //Constructors
    RBbst() { root = NO_NODE; }
    ~RBbst() { deallocate(root); }
/*
    //prints tree in Inorder
    void display() {
      cout << endl;
      print(root);
    }
*/
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
      root = insert(key, data, root);
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
