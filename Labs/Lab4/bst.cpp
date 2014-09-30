#include "bst.h"

/*
struct node {
  node *right,  //pointer to right child
       *left,   //pointer to left child
       *parent; //pointer to parent
  string data;
  int key;
};
*/

//node *root;

// delete all nodes in the subtree rooted at n,
//    and set n to null
void bst::deallocate(node* &n){
  if (n == NO_NODE) return;
  deallocate(n->left);
  deallocate(n->right);
  delete n;
  n = NO_NODE;
}
string bst::search(int k, node* &n){
  if (n == NO_NODE) return "nothing";
  else if (k < n->key){
    return search(k, n->left);
  }
  else if (k > n->key){
    return search(k, n->right);
  }
  else
    return n->data;
}

/*
string bst::find(int k, node* n){
  if (n==NO_NODE) return( NULL);
  else {
    //stub here -- doesn't work but returns the right type
    return (n->data);
  }
}
*/
// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
//  
bool bst::insert(int k, string d, node* &n){
  // if we've found the end of a chain,
  //    insert the node here
  if (n == NO_NODE) {
    n = new node;
    n->left = NO_NODE;
    n->right = NO_NODE;
    n->key = k;
    n->data = d;
    return 1;
  }
  //otherwise, do the stuff you tell it to
}

// if the subtree rooted at n contains a node whose key
//    matches k then remove it from the subtree, and return true,
//    otherwise return
bool bst::deleteElement(int k, node* &n){
  if (n==NO_NODE) return 0;
  if (n->key == k) {
    if (n->left==NO_NODE) {
      node* temp = n->right;
      delete n;
      n = temp;
      return 1;
    }
    if (n->right == NO_NODE) {
      node* temp = n->left;
      delete n;
      n= temp;
      return 1;
    }
    node* victim = n->right;
    // node* p = n; 
    // Somehow we must keep track of
    // whether victim is a right child or a left child
    // the rest is up to you
  }
  // action to take if current node is not the one to delete
  // WRITE CODE HERE
}

// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
void bst::print(node *n){
  if (n == NO_NODE) return;
  print(n->left);
  cout << n->key << ":" << n->data << endl;
  print(n->right);
}

// display the contents and structure of the subtree rooted at n,
// performed via preorder traversal
void bst::debugprint(node *n){
  if (n == NO_NODE) return;
  cout << n->key << ":" << n->data << " (";
  if (n->left) cout << n->left->key;
  else cout << "NULL";
  cout << "<-left,right->";
  if (n->right) cout << n->right->key;
  else cout << "NULL";
  cout << ") ";
  debugprint(n->left);
  debugprint(n->right);
}

void bst::swapElements(node* n, node* m){
  node temp;
  temp.data = n->data;
  n->data = m->data;
  m->data = temp.data;
  temp.key = n->key;
  n->key= m->key;
  m->key= temp.key;
}
