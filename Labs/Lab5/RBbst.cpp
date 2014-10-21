/************************************************************************
 Design Unit  : Lab5

 File Name    : RBbst.cpp

 Purpose      :

 Note         :

 Limitations  :

 Errors       : none known

 Modules      : RBbst.h

 Dependences  : RBbst.h
                assert.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 06  New version Initial code from bst.cpp
 1.1          DB      Oct 13  Sentinel implementation complete
 1.2          DB      Oct 14  Fixed multiple layers issue
*************************************************************************/
#include <assert.h>
#include "RBbst.h"
using namespace std;

/*
contained in RBbst hearder file
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         int colour;
  }; *root;
  * Sentinel;   */

// insert a new node in the RBbst rooted at n,
// returning a pointer to the root
RBbst::node * RBbst::insertNode(int key, string data, node *&n){
  //make new node with key and data
  node * current = new node;
  current->left = Sentinel;
  current->right = Sentinel;
  current->parent = Sentinel;
  current->key = key;
  current->data = data;
  current->colour = RED;
  //Empty tree
  if(n==Sentinel){
    current->colour=BLACK;
    n=current;
    return n;
  }
  //otherwise
  else{
    node * temp = new node;
    //find the spot to attach the new node
    temp=finding(n,key,0);
    //assign the new node to the find
    current->parent=temp;
    //if new node is greater than parent make right child
    if(key>=temp->key){
      temp->right=current;
    }
    //otherwise new node is left child
    else{
      temp->left=current;
    }
  }
  //check the insert for case 1
  n=insert_case1(current,n);
  return n;
}
//return a pointer to the node to which new node can be attached
RBbst::node * RBbst::finding(node *&n,int key,int i){
  node * temp = Sentinel;
  //if empty node, return node
  if(n == Sentinel){
    return n;
  }
  //if the node has been inserted return node
  if(i == 1){
    return temp;
  }
  //if nodes key is greater than key
  if(n->key > key){
    //if left child is Sentinel
    if(n->left==Sentinel){
      //assign n to temp
      temp=n;
      //set i to 1 and return temp
      i=1;
      return temp;
    }
    //otherwise continue to look to the left
    else{
      return finding(n->left,key,i);
    }
  }
  //if nodes key is less than key
  else{
    //if right child is Sentinel
    if(n->right==Sentinel){
      //assign n to temp
      temp=n;
      //set i to 1 and return temp
      i=1;
      return temp;
    }
    //otherwise continue to look to the right
    else
      return finding(n->right,key,i);
  }
}
//if the node is the root
RBbst::node * RBbst::insert_case1(node *&current, node *&n){
  //if parent is a Sentinel, than node is root and must be black
  if (current->parent == Sentinel){
    current->colour = BLACK;
  }
  //otherwise check case 2
  else{
    n=insert_case2(current,n);
  }
  return n;
}
//if parent is black then no change in colour required
RBbst::node * RBbst::insert_case2(node *&current, node *&n){
  //if the parents colour is black
  if (current->parent->colour == BLACK){
    return n;
  }
  //otherwise check case 3
  else{
    n=insert_case3(current,n);
  }
  return n;
}
//if uncle is red, colour swap with parent, uncle and grandparent
RBbst::node * RBbst::insert_case3(node *&current, node *&n){
  node *u = uncle(current);
  node *g = grandparent(current);
  //if uncle is red
  if ((u != Sentinel) && (u->colour == RED)) {
    //change colour of parent, uncle, and grandparent
    current->parent->colour = BLACK;
    u->colour = BLACK;
    g->colour = RED;
    //then insert case 1
    n=insert_case1(g,n);
  }
  //otherwise check case 4
  else {
    n=insert_case4(current,n);
  }
  return n;
}
//uncle is black child is left of right or right of left
RBbst::node * RBbst::insert_case4(node *&current, node *&n){
  //if current is right child and parent is left child
  node *g = grandparent(current);
  if ((current == current->parent->right) && (current->parent == g->left)) {
    //rotate left
    n=Double_rotate_left(current,n);
    current = current->left;
  }
  //otherwise if current is left child and parent is right
  else if ((current == current->parent->left) && (current->parent == g->right)) {
    //rotate right
    n=Double_rotate_right(current,n);
    current = current->right;
  }
  //otherwise check case 5
  else{
    n=insert_case5(current,n);
  }
  return n;
}
//uncle is black child is left of left or right of right
RBbst::node * RBbst::insert_case5(node *&current, node *&n){
  node *g = grandparent(current);
  //colour swap parent and grandparent
  current->parent->colour = BLACK;
  g->colour = RED;
  //if child is left of left
  if (current == current->parent->left)
    //rotate right
    n=rotate_right(current->parent,n);
  //otherwise rotate left
  else
    n=rotate_left(current->parent,n);
  return n;
}
//return a pointer to uncle
RBbst::node * RBbst::uncle(node *&current){
  node *g = grandparent(current);
  if (g == Sentinel)
    return Sentinel;
  //if current parent is left then uncle is right
  if (current->parent == g->left)
    return g->right;
  //otherwise uncle is left
  else
    return g->left;
}
//return a pointer to grandparent
RBbst::node * RBbst::grandparent(node *&current){
  //if current and parent are not sentinels, return grandparent
  if ((current != Sentinel) && (current->parent != Sentinel))
    return current->parent->parent;
  //otherwise return sentinel
  else
    return Sentinel;
}
//rotate node to left
RBbst::node * RBbst::rotate_left(node *current, node *n){
  node *GP = grandparent(current);
  node *P = current->parent;
  node *C = current;
  node *CR = current->right;
  node *CL = current->left;
  if (GP != Sentinel){
    GP->right = current;
  }
  current->parent = GP;
  P->parent = current;
  P->right = CL;
  C->left = P;
  n=current;
  return n;
}
//rotate node to right
RBbst::node * RBbst::rotate_right(node *current, node *n){
  node *GP = grandparent(current);
  node *P = current->parent;
  node *C = current;
  node *CR = current->right;
  node *CL = current->left;
  if (GP != Sentinel){
    GP->left = current;
  }
  current->parent = GP;
  P->parent = current;
  P->left = CR;
  current->right = P;
  n=current;
  return n;
}
//Double the rotate left
RBbst::node * RBbst::Double_rotate_left(node *current, node *n){
  node *currentgrand = grandparent(current);
  node *currentparent = current->parent;
  node *currentgg=currentgrand->parent;
  currentgrand->left = current;
  current->parent = currentgrand;
  current->left = currentparent;
  currentparent->parent = current;
  currentparent->right = current->right;
  currentgg->right = current;
  current->parent = currentgg;
  current->right = currentgrand;
  currentgrand->parent = current;
  currentgrand->left = currentparent->left;
  //if currents great grandparent is not a sentinel
  if(currentgg!=Sentinel){
    //if current grand is a left child
    if(currentgg->left==currentgrand){
      currentgg->left=current->parent->parent;
    }
    //otherwise current grand is a right child
    else if(currentgg->right==currentgrand){
      currentgg->right=current->parent->parent;
    }
  }
  else n=current->parent;
  return n;
}
//Double rotate node to right
RBbst::node * RBbst::Double_rotate_right(node *current, node *n){
  node *currentgrand = grandparent(current);
  node *currentparent = current->parent;
  node *currentgg=currentgrand->parent;
  currentgrand->right = current;
  current->parent = currentgrand;
  current->right = currentparent;
  currentparent->parent = current;
  currentparent->left = current->left;
  currentgg->left = current;
  current->parent = currentgg;
  current->left = currentgrand;
  currentgrand->parent = current;
  currentgrand->right = currentparent->right;
  //if currents great grandparent is not a sentinel
  if(currentgg!=Sentinel){
    //if current grand is a left child
    if(currentgg->left==currentgrand){
      currentgg->left=current->parent->parent;
    }
    //otherwise current grand is a right child
    else if(currentgg->right==currentgrand){
      currentgg->right=current->parent->parent;
    }
  }
  else n=current->parent;
  return n;
}
// find the node with key and return data
string RBbst::search(int key, node *&current){
  // if empty tree
  if (current == Sentinel) return "nothing";
  // otherwise if nodes key is > than k
  else if (key < current->key){
    return search(key, current->left);
  }
  // otherwise if nodes key is < k
  else if (key > current->key){
    return search(key, current->right);
  }
  // otherwise return data
  else
    return current->data;
}
//print inorder as specified on board in lab
void RBbst::print(node *&current){
   int c = current->colour;
   char C;
   if (c == 1){C = 'b';}
   else C = 'r';
   //if node is a sentinel return
   if (current == Sentinel) return;
   //print left tree first
   if (current->left != Sentinel) print(current->left);
   //print currents information if parent is a sentinel
   if (current->parent == Sentinel){
     //5:a (N b 2 7)
     cout << current->key << ":" << current->data << " (" << "N " << C << " "
          << current->left->key << " " << current->right->key << ")" << endl;
   }
   //currents parent is not a sentinel
   else if (current->parent != Sentinel){
     //5:a (5 b N N)
     if ((current->left == Sentinel) && (current->right == Sentinel)){
       cout << current->key << ":" << current->data << " (" << current->key << " " << C
          << " " << "N " << "N" << ")" << endl;
     }
     //5:a (5 b N 6)
     else if ((current->left == Sentinel) && (current->right != Sentinel)){
       cout << current->key << ":" << current->data << " (" << current->key << " " << C
          << " " << "N " << current->right->key << ")" << endl;
     }
     //5:a (5 b 2 N)
     else if ((current->left != Sentinel) && (current->right == Sentinel)){
       cout << current->key << ":" << current->data << " (" << current->key << " " << C
          << " " << current->left->key << " N" << ")" << endl;
     }
     //5:a (5 b 2 6)
     else {
     cout << current->key << ":" << current->data << " (" << current->key << " " << C
          << " " << current->left->key << " " << current->right->key << ")" << endl;
     }
   }
   //print right tree last
   if (current->right != Sentinel) print(current->right);
}
//Change to printout as specified in Lab5 Preorder Print
//Print tree in preorder
void RBbst::PreOrdprint(node *&current){
   int c = current->colour;
   char C;
   if (c == 1){C = 'b';}
   else C = 'r';
   //if current is sentinel return
   if (current == Sentinel) {return;}
   //print current node information
   else {
     cout << current->key << ":" << current->data << " " << C << " (";
     if (current->left != Sentinel) cout << current->left->key;
     else cout << "N";
     cout << "<- " << current->key << " ->";
     if (current->right != Sentinel) cout << current->right->key;
     else cout << "N";
     cout << ") " << endl;
   }
   //print left tree
   if (current->left != Sentinel) PreOrdprint(current->left);
   //print right tree
   if (current->right != Sentinel) PreOrdprint(current->right);
   return;
}
// display the contents and structure of the subtree rooted at current,
// performed via preorder traversal
void RBbst::debugprint(node *&current){
   //if current is sentinel return
   if (current == Sentinel) return;
   //print current node information
   else{
     cout << current->key << ":" << current->data << " (";
     if (current->left->key != -99999999) cout << current->left->key;
     else cout << "Sentinel";
     cout << "<-left,right->";
     if (current->right->key != -99999999) cout << current->right->key;
     else cout << "Sentinel";
     cout << ") ";
   }
   //print left tree
   if (current->left != Sentinel) debugprint(current->left);
   //print right tree
   if (current->right != Sentinel) debugprint(current->right);
}
// if the subtree rooted at n contains a node whose key
// matches k then remove it from the subtree
bool RBbst::deleteElement(int key, node *&root){
  node* child;
  //find the node to be removed in the tree
  node* n = finding(root,key,0);
  //if removal node is sentinel, return
  if (n == Sentinel){
    return 0;
  }
  //if removal node has left and right children
  if (n->left != Sentinel && n->right != Sentinel){
    //find the predecessor on the left tree
    node* pred = maximum_node(n->left);
    //overwrite removal nodes information with predecessor
    n->key = pred->key;
    n->data = pred->data;
    n = pred;
  }
  //check if children are sentinels
  assert(n->left == Sentinel || n->right == Sentinel);
  child = n->right == Sentinel ? n->left  : n->right;
  //if colour is black, set to colour of child
  if (node_colour(n) == BLACK){
    n->colour = node_colour(child);
    //delete case 1
    delete_case1(root, n);
  }
  //replace node
  replace_node(root, n, child);
  //delete the node from memory
  delete n;
  //verify the properties of a Red Black tree
  verify_properties(root);
  return 1;
}
// Replace a node
void RBbst::replace_node(node *&root, node *&n, node *&child){
    //if parent is a sentinel
    if (n->parent == Sentinel){
      //child is assigned to root
      root = child;
    }
    //otherwise
    else{
      //if node is a left child
      if (n == n->parent->left){
        //set grandparent left child to child
        n->parent->left = child;
      }
      //otherwise
      else{
        //set grantparent right child to child
        n->parent->right = child;
      }
    }
    //if child is not a sentinel
    if (child != Sentinel){
      //set childs parent to nodes parent
      child->parent = n->parent;
    }
}
// Returns Maximum node
RBbst::node * RBbst::maximum_node(node *&n){
    //check if node is not a sentinel
    assert (n != Sentinel);
    //while right child is not a sentinel go right
    while (n->right != Sentinel){
        n = n->right;
    }
    return n;
}
// Deleting Case 1
void RBbst::delete_case1(node *& root, node *&n){
  //if nodes parent is sentinel, nothing to do
  if (n->parent == Sentinel){
    return;
  }
  //otherwise delete case 2
  else{
    delete_case2(root, n);
  }
}
// Deleting Case 2
void RBbst::delete_case2(node *& root, node *&n){
  //if the sibling of the node is red
  if (node_colour(sibling(n)) == RED){
    //colour swam nodes parent and sibling
    n->parent->colour = RED;
    sibling(n)->colour = BLACK;
    //if node is left child
    if (n == n->parent->left){
      //rotate left
      rotate_left(root, n->parent);
    }
    //otherwise rotate right
    else {
      rotate_right(root, n->parent);
    }
  }
  //otherwise delete case 3
  delete_case3(root, n);
}
// Deleting Case 3
void RBbst::delete_case3(node *& root, node *&n){
  //if nodes parent is black, nodes sibling is black, nodes neice and nephew are black
  if (node_colour(n->parent) == BLACK && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->left) == BLACK && node_colour(sibling(n)->right) == BLACK){
    //set siblings colour to red
    sibling(n)->colour = RED;
    //delete case 1
    delete_case1(root, n->parent);
  }
  //otherwise delete case 4
  else {
    delete_case4(root, n);
  }
}
// Deleting Case 4
void RBbst::delete_case4(node *& root, node *&n){
  //if nodes parent is red, sibling is black, neice and nephew are black
  if (node_colour(n->parent) == RED && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->left) == BLACK && node_colour(sibling(n)->right) == BLACK){
    //set siblings colour to red and parent to black
    sibling(n)->colour = RED;
    n->parent->colour = BLACK;
  }
  //otherwise delete case 5
  else {
    delete_case5(root, n);
  }
}
// Deleting Case 5
void RBbst::delete_case5(node *& root, node *&n){
  //if node is a left child and sibling is black, neice is red and nephew is black
  if (n == n->parent->left && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->left) == RED && node_colour(sibling(n)->right) == BLACK){
    //change sibling to red and neice to black
    sibling(n)->colour = RED;
    sibling(n)->left->colour = BLACK;
    //rotate right
    rotate_right(root, sibling(n));
  }
  //otherwise if node is right child, sibling is black, nephew is red and neice is black
  else if (n == n->parent->right && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->right) == RED && node_colour(sibling(n)->left) == BLACK){
    //change sibling to red and nephew to black
    sibling(n)->colour = RED;
    sibling(n)->right->colour = BLACK;
    //rotate left
    rotate_left(root, sibling(n));
  }
  //otherwise delete case 6
  delete_case6(root, n);
}
// Deleting Case 6
void RBbst::delete_case6(node *& root, node *&n){
  //set siblings colour to parents colour
  sibling(n)->colour = node_colour(n->parent);
  //set parent to black
  n->parent->colour = BLACK;
  //if node is left child
  if (n == n->parent->left){
    //check if nephew is red
    assert (node_colour(sibling(n)->right) == RED);
    //set nephew to black
    sibling(n)->right->colour = BLACK;
    //rotate left
    rotate_left(root, n->parent);
  }
  //otherwise
  else{
    //check if neice is red
    assert (node_colour(sibling(n)->left) == RED);
    //set neice to black
    sibling(n)->left->colour = BLACK;
    //rotate right
    rotate_right(root, n->parent);
  }
}
// Return Sibling of Node
RBbst::node * RBbst::sibling(node *&n){
  //check that node and nodes parent are not sentinel
  assert (n != Sentinel);
  assert (n->parent != Sentinel);
  //if node is left child
  if (n == n->parent->left){
    //return right child
    return n->parent->right;
  }
  //otherwise return left child
  else{
    return n->parent->left;
  }
}
// Verifying Properties of Red black Tree
void RBbst::verify_properties(node *&n){
  //Property 1 - each node must be red or black
  verify_property_1 (n);
  //Property 2 - root must be black
  verify_property_2 (n);
  //Property 3 - no two consecutive red nodes
  verify_property_3 (n);
  //Property 4 - black height must be the same
  verify_property_4 (n);
}
// Verifying Property 1 Each node must be red or black
void RBbst::verify_property_1(node *&n){
  //check that node is either red or black
  assert (node_colour(n) == RED || node_colour(n) == BLACK);
  //if node is a sentinel, return
  if (n == Sentinel){
    return;
  }
  //verify property 1 for left child
  verify_property_1(n->left);
  //verify property 1 for right child
  verify_property_1(n->right);
}
// Verifying Property 2 Root node must be black
void RBbst::verify_property_2(node *&n){
  //check root colour is black
  assert (node_colour(n) == BLACK);
}
// Verifying Property 3 If a node is red, it's children and parent must be black
void RBbst::verify_property_3(node *&n){
  //if node is red
  if (node_colour(n) == RED){
    //check left child, right child, and parent are black
    assert (node_colour(n->left) == BLACK);
    assert (node_colour(n->right) == BLACK);
    assert (node_colour(n->parent) == BLACK);
  }
  //if node is sentinel
  if (n == Sentinel){
    return;
  }
  //verify property 4 on left child
  verify_property_4(n->left);
  //verify property 4 on right child
  verify_property_4(n->right);
}
// Verifying Property 4 The Black height must be the same for all leaves
void RBbst::verify_property_4(node *&n){
  //set count to -1 and call helper
  int black_count_path = -1;
  verify_property_4_helper(n, 0, &black_count_path);
}

void RBbst::verify_property_4_helper(node *&n, int black_count, int* black_count_path){
  //if node colour is black, increment black count
  if (node_colour(n) == BLACK){
    black_count++;
  }
  //if node is a sentinel
  if (n == Sentinel){
    //if count is -1, set path black count to black count
    if (*black_count_path == -1){
      *black_count_path = black_count;
    }
    //otherwise
    else {
      //check if black count is path black count
      assert (black_count == *black_count_path);
    }
    return;
  }
  //verify property 4 help on left child
  verify_property_4_helper(n->left,  black_count, black_count_path);
  //verify property 4 help on right child
  verify_property_4_helper(n->right, black_count, black_count_path);
}
 //Returns colour of a node
int RBbst::node_colour(node *n){
  return n->colour;
}
// delete all nodes in the subtree rooted at n, and set n to null
void RBbst::deallocate(node* &n){
  //if node is a sentinel return
   if (n == Sentinel) return;
  //deallocate left child
  deallocate(n->left);
  //deallocate right child
  deallocate(n->right);
  //delete node
  delete n;
  //set node to sentinel
  n = Sentinel;
}
// swap data and key between two nodes
void RBbst::swapElements(node* n, node* m){
  //transfer information from first node to temp
  node temp;
  temp.data = n->data;
  temp.key = n->key;
  //transfer information from second node to first
  n->data = m->data;
  n->key= m->key;
  //transfer information from temp to second
  m->data = temp.data;
  m->key= temp.key;
}
