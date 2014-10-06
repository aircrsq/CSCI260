/************************************************************************
 Design Unit  : Lab5

 File Name    : RBbst.cpp

 Purpose      :

 Note         :

 Limitations  :

 Errors       : none known

 Modules      : bst.h

 Dependences  : bst.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 06  New version
*************************************************************************/
#include "bst.h"
using namespace std;

/*
  enum colour { r, b };
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         enum colour colour;
  };
  *root;   */

// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
bool bst::insert(int k, string d, node* &n){
  // insert the node at the appropiate location
  // if root is null, create a new node with information and return true
  if (n == NO_NODE) {
   	n = new node;
	n->left = NO_NODE;
	n->right = NO_NODE;
	n->key = k;
	n->data = d;
        n->colour = r;
   	return 1;
  }
  // if key is < new key and there are nodes to the right
  // call insert with the right node
  else if ((n->key < k) && (n->right!= NO_NODE)){
    return insert(k, d, n->right);
  }
  // if key is > new key and there are nodes to the left
  // call insert with the left node
  else if ((n->key > k) && (n->left != NO_NODE)) {
    return insert(k, d, n->left);
  }
  // if key is > new key and there are no nodes to the left
  // attach the new node to the left
  else if ((n->key > k) && (n->left == NO_NODE)){
    if (Attach(k, d, n, n->left));
    return 1;
  }
  // if key is < new key and there are no nodes to the right
  // attach the new node to the right
  else if ((n->key < k) && (n->right == NO_NODE)) {
    if (Attach(k, d, n, n->right));
    return 1;
  }
  // otherwise key = new key
  // attach an equal key node
  else {
    if (AttachEqual(k, d, n));
    return 1;
  }
}

// create new node with the input key and data
// attach node c to node n, returning true
bool bst::Attach(int key, string data, node *&n, node *&c){
  node * tmp = new node;
  tmp->key = key;
  tmp->data = data;
  tmp->parent = n;
  tmp->left = NO_NODE;
  tmp->right = NO_NODE;
  tmp->colour = r;
  c = tmp;
  return 1;
}

// insert a node of equal value with different data attached to n
// return true is successful
bool bst::AttachEqual(int key, string data, node *&n){
  node * tmp = n->parent;
  // if there are no nodes to the left
  // attach the new node to the left
  if (n->left == NO_NODE) { return Attach(key, data, n, n->left);}
  // if there are no nodes to the right
  // attach new node to the right
  else if (n->right == NO_NODE) { return Attach(key, data, n, n->right);}
  // if we are a left child attach the node to the left
  else if (tmp->left = n) { return leftjoin(key, data, n);}
  // if we are a right child attach the node to the right
  else if (tmp->right = n) { return rightjoin(key, data, n);}
}

// join new node to left child of n
// return true
bool bst::leftjoin(int key, string data, node *&n) {
  node *tmp = new node;
  tmp->key = key;
  tmp->data = data;
  tmp->right = NO_NODE;
  tmp->parent = n-> parent;
  tmp->colour = r;
  tmp->left = n;
  n->parent = tmp;
  return 1;
}

// join new node to right child of n
// return true
bool bst::rightjoin(int key, string data, node *&n) {
  node *tmp = new node;
  tmp->key = key;
  tmp->data = data;
  tmp->left = NO_NODE;
  tmp->parent = n-> parent;
  tmp->colour = r;
  tmp->right = n;
  n->parent = tmp;
  return 1;
}

// find the node with key to be deleted
// return pointer to victim
bst::node *bst::FindVictim(int key, node *&n){
  node *Tmp = n;
  // if keys match return node
  if (Tmp->key == key) {return Tmp; }
  // if node key is > key find victim down left tree
  else if (Tmp->key > key) {return FindVictim(key, Tmp->left);}
  // if node key is < key find victim down right tree
  else if (n->key < key) {return FindVictim(key, Tmp->right);}
}

// find the successor going down the left branch
// return pointer to successor
bst::node *bst::LeftSuccessor(int key, node *&victim){
  // if there are no nodes on the right child or
  // the keys match return node
  if ((victim->right == NO_NODE) || (victim->key == key)) { return victim; }
  // otherwise look to the right for successor
  else return LeftSuccessor(key, victim->right);
}

// find the successor going down the right branch
// return pointer to successor
bst::node *bst::RightSuccessor(int key, node *&victim){
  // if there are no nodes on the left child or
  // the keys match return node
  if ((victim->left == NO_NODE) || (victim->key == key)) {return victim;}
  // otherwise look to the left for sucessor
  else return RightSuccessor(key, victim->left);
}

// delete all nodes in the subtree rooted at n,
// and set n to null
void bst::deallocate(node* &n){
   if (n == NO_NODE) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = NO_NODE;
}

// transfer data and key from successor to victim
void bst::TDK(node *&Vic, node *&Suc){
  Vic -> key = Suc -> key;
  Vic -> data = Suc -> data;
}

// change pointer of left child parent to grandparent
// and grandparent right child to grandchild
void bst::RCL(node *&SP, node *&SC){
  SP->right = SC;
  SC->parent = SP;
}

// change pointer of right child parent to grandparent
// and grandparent left child to grandchild
void bst::RCR(node *&SP, node *&SC){
  SP->left = SC;
  SC->parent = SP;
}

// if the subtree rooted at n contains a node whose key
// matches k then remove it from the subtree, and return true,
// otherwise return
bool bst::deleteElement(int k, node* &n){
  // empty tree
  if (n==NO_NODE) return 0;
  node * Victim = FindVictim(k, n);
  // if victim has left nodes
  if (Victim->left != NO_NODE) {
    // look for successor to the left
    node * Successor = LeftSuccessor(k, Victim->left);
    // switch data and key
    TDK(Victim, Successor);
    // if successor has left children rotate child left
    if (Successor-> left != NO_NODE) {RCL(Successor->parent, Successor->left);}
    // otherwise if successor has no left child point parent to null
    else if (Successor-> left == NO_NODE){Successor->parent->right = NO_NODE;}
    // delete the successor
    delete Successor;
  }
  // if victim has right nodes
  else if (Victim->right != NO_NODE) {
    // look for successor to the right
    node * Successor = RightSuccessor(k, Victim->right);
    // switch data and key
    TDK(Victim, Successor);
    // if successor has right children rotate child right
    if (Successor-> right != NO_NODE) {RCR(Successor->parent, Successor->right);}
    // otherwise if successor has no right child point parent to null
    else if (Successor-> right == NO_NODE){Successor->parent->left = NO_NODE;}
    // delete the successor
    delete Successor;
  }
  // victim is a leaf and left child
  else if ((Victim->parent != NO_NODE) && (Victim->parent->left == Victim)){
    Victim->parent->left = NO_NODE;
    delete Victim;
  }
  // victim is a leaf and right child
  else if ((Victim->parent != NO_NODE) && (Victim->parent->right == Victim)){
    Victim->parent->right = NO_NODE;
    delete Victim;
  }
  return 1;
}

// find the node with key
// return data
string bst::search(int k, node* &n){
  // if empty tree
  if (n == NO_NODE) return "nothing";
  // otherwise if nodes key is > than k
  else if (k < n->key){
    return search(k, n->left);
  }
  // otherwise if nodes key is < k
  else if (k > n->key){
    return search(k, n->right);
  }
  // otherwise return data
  else
    return n->data;
}

// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
void bst::print(node *n){
   if (n == NO_NODE) return;
   print(n->left);
   if (n->parent == NO_NODE){
     cout << n->key << ":" << n->data << " (" << n->colour << ", parent = null)" << endl;
   }
   else {
     cout << n->key << ":" << n->data << " (" << n->colour << ", parent = " << n->parent->key
          << ")" << endl;
   }
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

// swap data and key between two nodes
void bst::swapElements(node* n, node* m){
   node temp;
   temp.data = n->data;
   n->data = m->data;
   m->data = temp.data;

   temp.key = n->key;
   n->key= m->key;
   m->key= temp.key;
}
