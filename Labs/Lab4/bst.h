#ifndef BST 
#define BST

#include <string>
#include <iostream>
using namespace std;

const int NO_NODE = 0;

class bst{
  private:
    struct node {
      node *right,  //pointer to right child
           *left,   //pointer to left child
           *parent; //pointer to parent
      string data;
      int key;
    };
    // we maintain a pointer to the root of the tree
    node *root;

    // private, recursive routines
    // (used by the public methods)
    void deallocate(node* &n);
    bool insert(int k, string d, node* &n);
    bool deleteElement(int k, node* &n);
    string search(int k, node* &n);
    void print(node *n);
    void debugprint(node *n); 
    void swapElements(node* n, node* m);
    node * Attach(int key, string data, node * &n);
    void initialize(int key, string data, node* &n);
    void AttachEqual(int key, string data, node * &n);
    node * leftjoin(int key, string data, node *&n);
    node * rightjoin(int key, string data, node *&n);

  public:
    bst() { root = NULL; }
    ~bst() { deallocate(root); }
    void display() { print(root); }
    void find(int k) {
      string SearchResult = search(k,root);
      cout << SearchResult;
    }
    void debug() { debugprint(root); }
    bool insert(int k, string d) {
      if (insert(k, d, root)) 
        return true;
      else return false;
    }
    bool deleteElement(int k) {
      if (deleteElement(k, root)) 
        return true;
      else return false;
    }
//    string find(int k) {
//      node* temp = find(k, root));
//      if (temp==NO_NODE) return NO_STRING;
//        return temp->data;
//    }
};
#endif
