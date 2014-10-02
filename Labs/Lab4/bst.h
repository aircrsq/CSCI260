#ifndef BST 
#define BST

#include <string>
#include <iostream>
using namespace std;

const int NO_NODE = 0;

class bst{
   private:
      struct node {
          node *right, *left, *parent;
          string      data;
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
      void swapElements(node* n, node* m);

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
};

#endif
