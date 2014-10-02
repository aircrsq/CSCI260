#include "bst.h"
using namespace std;
// struct node {
//     node *right, *left, *parent;
//     string      key, data;
// } *root;

// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
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
  else if ((n->key < k) && (n->right!= NO_NODE)){
    return insert(k, d, n->right);
  }
  else if ((n->key > k) && (n->left != NO_NODE)) {
    return insert(k, d, n->left);
  }
  else if ((n->key > k) && (n->left == NO_NODE)){
    if (Attach(k, d, n, n->left));
    return 1;
  }
  else if ((n->key < k) && (n->right == NO_NODE)) {
    if (Attach(k, d, n, n->right));
    return 1;
  }
  else {
    if (AttachEqual(k, d, n));
    return 1;
  }
}

//return an attached node
bool bst::Attach(int key, string data, node *&n, node *&c){
  node * tmp = new node;
  tmp->key = key;
  tmp->data = data;
  tmp->parent = NO_NODE;
  tmp->left = NO_NODE;
  tmp->right = NO_NODE;
  tmp->parent = n;
  c = tmp;
  return 1;
}

bool bst::AttachEqual(int key, string data, node *&n){
  node * tmp = n->parent;
  if (n->left == NO_NODE) { return Attach(key, data, n, n->left);}
  else if (n->right == NO_NODE) { return Attach(key, data, n, n->right);}
  else if (tmp->left = n) { return leftjoin(key, data, n);}
  else if (tmp->right = n) { return rightjoin(key, data, n);}
}

bool bst::leftjoin(int key, string data, node *&n) {
  node *tmp = new node;
  tmp->key = key;
  tmp->data = data;
  tmp->right = NO_NODE;
  tmp->parent = n-> parent;
  tmp->left = n;
  n->parent = tmp;
  return 1;  
}

bool bst::rightjoin(int key, string data, node *&n) {
  node *tmp = new node;
  tmp->key = key;
  tmp->data = data;
  tmp->left = NO_NODE;
  tmp->parent = n-> parent;
  tmp->right = n;
  n->parent = tmp;
  return 1;  
}

bst::node *bst::FindVictim(int key, node *&n){
  node *Tmp = n;
  if (Tmp->key == key) {return Tmp; }
  else if (Tmp->key > key) {return FindVictim(key, Tmp->left);}
  else if (n->key < key) {return FindVictim(key, Tmp->right);}
}

bst::node *bst::LeftSuccessor(int key, node *&victim){
  if ((victim->right == NO_NODE) || (victim->key = key)) {return victim;}
  else return LeftSuccessor(key, victim->right);
}

bst::node *bst::RightSuccessor(int key, node *&victim){
  if ((victim->left == NO_NODE) || (victim->key = key)) {return victim;}
  else return RightSuccessor(key, victim->left);
}

// delete all nodes in the subtree rooted at n,
//    and set n to null
void bst::deallocate(node* &n){
   if (n == NO_NODE) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = NO_NODE; 
}

void bst::TDK(node *&Vic, node *&Suc){
  Vic -> key = Suc -> key;
  Vic -> data = Suc -> data;
}

void bst::RCL(node *&SP, node *&SC){
  SP->right = SC;
  SC->parent = SP;
}

void bst::RCR(node *&SP, node *&SC){
  SP->left = SC;
  SC->parent = SP;
}
// if the subtree rooted at n contains a node whose key
//    matches k then remove it from the subtree, and return true,
//    otherwise return 
bool bst::deleteElement(int k, node* &n){
  if (n==NO_NODE) return 0;
  node * Victim = FindVictim(k, n);
  if (Victim->left != NO_NODE) {
    node * Successor = LeftSuccessor(k, Victim->left);
    TDK(Victim, Successor);
    RCL(Successor->parent, Successor->left);
    deallocate(Successor);
  }
  else if (Victim->right != NO_NODE) {
    node * Successor = RightSuccessor(k, Victim->right);
    TDK(Victim, Successor);
    RCR(Successor->parent, Successor->right);
    deallocate(Successor);
  }
  else if (Victim->parent->left == Victim){
    Victim->parent->left = NO_NODE;
    deallocate(Victim);
  }
  else if (Victim->parent->right == Victim){
    Victim->parent->right = NO_NODE;
    deallocate(Victim);
  }
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

// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
void bst::print(node *n)
{
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
