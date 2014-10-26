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
void RBbst::insertNode(int key, string data, node *&n){
  //make new node with key and data
  node * current = new node;
  current->left = Sentinel;
  current->right = Sentinel;
  current->parent = Sentinel;
  current->key = key;
  current->data = data;
  current->colour = RED;
  node * temp = new node;
  //find the spot to attach the new node
  temp=finding(n,key,0);
  //assign the new node to the find
  current->parent=temp;
  //if new node is greater than parent make right child
  if (n != Sentinel){
    if(key>=temp->key){
      temp->right=current;
    }
    //otherwise new node is left child
    else{
      temp->left=current;
    }
  }
  //check the insert for case 1
  insert_case1(current,n);
  //verify_properties(n);
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
  if (n->key == key){
    return n;
  }
  //if nodes key is greater than key
  else if(n->key > key){
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
  else if (n->key < key){
    //if right child is Sentinel
    if(n->right==Sentinel){
      //assign n to temp
      temp=n;
      //set i to 1 and return temp
      i=1;
      return temp;
    }
    //otherwise continue to look to the right
    else{
      return finding(n->right,key,i);
    }
  }
}
//if the node is the root
void RBbst::insert_case1(node *&current, node *&n){
  //if parent is a Sentinel, than node is root and must be black
  if (current->parent == Sentinel){
    current->colour = BLACK;
    root = current;
  }
  //otherwise check case 2
  else{
    insert_case2(current,n);
  }
}
//if parent is black then no change in colour required
void RBbst::insert_case2(node *&current, node *&n){
  //if the parents colour is black
  if (current->parent->colour == BLACK){
    return;
  }
  //otherwise check case 3
  else{
    insert_case3(current,n);
  }
}
//if uncle is red, colour swap with parent, uncle and grandparent
void RBbst::insert_case3(node *&current, node *&n){
  node *u = uncle(current);
  node *g = grandparent(current);
  //if uncle is red
  if ((u->colour == RED) && (u != Sentinel)) {
    //change colour of parent, uncle, and grandparent
    current->parent->colour = BLACK;
    u->colour = BLACK;
    g->colour = RED;
    //then insert case 1
    insert_case1(g,n);
  }
  //otherwise check case 4
  else {
    insert_case4(current,n);
  }
}
//uncle is black child is left of right or right of left
void RBbst::insert_case4(node *&current, node *&n){
  node *g = grandparent(current);
    //if current is right child and parent is left child
  if ((current == current->parent->right) && (current->parent == g->left)) {
    //Double rotate left right
    rotate_left(current,n);
    current = current->left;
  }
  //otherwise if current is left child and parent is right
  else if ((current == current->parent->left) && (current->parent == g->right)) {
    //Double rotate right left
    rotate_right(current,n);
    current = current->right;
//    current->colour = BLACK;
//    current->left->colour = RED;
  }
  //otherwise check case 5
  insert_case5(current,n);
}
//uncle is black child is left of left or right of right
void RBbst::insert_case5(node *&current, node *&n){
  node *g = grandparent(current);
  //colour swap parent and grandparent
  current->parent->colour = BLACK;
  if (g != Sentinel){
    g->colour = RED;
  }
  //if child is left of left
  if (current == current->parent->left){
    //rotate right
    rotate_right(current->parent,n);
  }
  //otherwise child is right of right
  else{
    rotate_left(current->parent,n);
  }
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
// Return Sibling of Node
RBbst::node * RBbst::sibling(node *&current){
  //check that node and nodes parent are not sentinel
  if (current != Sentinel){
    if (current->parent != Sentinel){
      if (current == current->parent->left){
      //return right child
        return current->parent->right;
      }
      //otherwise return left child
      else{
        return current->parent->left;
      }
    }
  }
}
//rotate node to left
void RBbst::rotate_left(node *current, node *n){
  node *GP = grandparent(current);
  node *P = current->parent;
  node *C = current;
  node *CR = current->right;
  node *CL = current->left;
  P->parent = current;
  current->parent = GP;
  P->right = CL;
  current->left = P;
  if (current->parent == Sentinel){
    root=current;
  }
  if (GP != Sentinel){
    if (GP->left == P){
      GP->left = current;
    }
    else{
      GP->right = current;
    }
  }
}
//rotate node to right
void RBbst::rotate_right(node *current, node *n){
  node *GP = grandparent(current);
  node *P = current->parent;
  node *C = current;
  node *CR = current->right;
  node *CL = current->left;
  P->parent = current;
  current->parent = grandparent(current);
  P->left = current->right;
  current->right = P;
  if (current->parent == Sentinel){
    root=current;
  }
  if (GP != Sentinel){
    if (GP->left == P){
      GP->left = current;
    }
    else{
      GP->right = current;
    }
  }
}
//Double the rotate left
RBbst::node * RBbst::Double_rotate_left(node *current, node *n){
  node *currentgrand = grandparent(current);
  node *currentparent = current->parent;
  node *currentgg=currentgrand->parent;
  currentgrand->left = current;
  current->parent = currentgrand;
  currentparent->right = current->right;
  current->left = currentparent;
  currentparent->parent = current;

  currentgg->right = current;
  current->parent = currentgg;
  current->right = currentgrand;
  currentgrand->parent = current;
  currentgrand->left = current->right;
  //if currents great grandparent is not a sentinel
  if(currentgg!=Sentinel){
    n=current->parent;
    //if current grand is a left child
    if(currentgg->left==currentgrand){
      currentgg->left=current;
    }
    //otherwise current grand is a right child
    else if(currentgg->right==currentgrand){
      currentgg->right=current;
    }
  }
  else {
    n=current;
  }
  return n;
}
//Double rotate node to right
RBbst::node * RBbst::Double_rotate_right(node *current, node *n){
  node *currentgrand = grandparent(current);
  node *currentparent = current->parent;
  node *currentgg=currentgrand->parent;
  currentgrand->right = current;
  current->parent = currentgrand;
  currentparent->left = current->left;
  current->right = currentparent;
  currentparent->parent = current;
  currentgg->left = current;
  current->parent = currentgg;
  current->left = currentgrand;
  currentgrand->parent = current;
  currentgrand->right = currentparent->left;
  //if currents great grandparent is not a sentinel
  if(currentgg!=Sentinel){
    n=current->parent;
    //if current grand is a left child
    if(currentgg->left==currentgrand){
      currentgg->left=current;
    }
    //otherwise current grand is a right child
    else if(currentgg->right==currentgrand){
      currentgg->right=current;
    }
  }
  else {
    n=current;
  }
  return n;
}
//replace node
void RBbst::replace_node(node *n, node *current, node * newn){
/*    if (current->parent == NULL){
        n->parent = newn;
    }
    else{
        if (current == current->parent->left)
            current->parent->left = newn;
        else
            current->parent->right = newn;
    }   */
    if (newn != NULL){
        newn->parent = current->parent;
    }
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
bool RBbst::deleteElement(int key, node *&n){
  node * child = Sentinel;
  node * predecessor;
  //Find the node to delete
  node * DeleteNode = finding(n,key,0);
  //if there is a left subtree search for a predecessor starting at the left child
  if (DeleteNode->left != Sentinel){
    predecessor = maximum_node(DeleteNode->left);
  }
  //otherwise no predecessor exists
  else {
    predecessor = Sentinel;
  }
  if (predecessor->left != Sentinel){
    child = predecessor->left;
  }
  else{
    child = Sentinel;
  }
  if (predecessor != Sentinel){
    //swap the key and data
    swapElements(DeleteNode, predecessor);
    //if node predecessor is red, attach left child to parent
    if (node_colour(predecessor) == RED){
      //left child is sentinel
      if (predecessor->left != Sentinel){
        predecessor->parent->left = predecessor->left;
      }
      else if (predecessor->left == Sentinel){
        predecessor->parent->left = Sentinel;
      }
      //left child is subtree
      else {}
    }
    //if colour is black, set to colour of child
    else if (node_colour(predecessor) == BLACK){
      if (child->colour == RED){
        child->colour = BLACK;
        predecessor->parent->right = child;
        child->parent = predecessor->parent;
      }
      else if (child != Sentinel){
        delete_case1(child, root);
      }
      else {
        delete_case1(predecessor, n);
        delete predecessor;
      }
    }
  }
  //if predecessor is Sentinel
  else if (predecessor == Sentinel){
    //if node colour is black
    if (DeleteNode->colour == BLACK){
      delete_case1(DeleteNode, n);
      //if
      if (DeleteNode->parent->left == DeleteNode){
        DeleteNode->parent->left = Sentinel;
      }
      else if (DeleteNode->parent->right == DeleteNode){
        DeleteNode->parent->right = DeleteNode->left;
      }
      delete DeleteNode;
    }
    //otherwise the node colour is red
    else {
      if (DeleteNode->parent->left == DeleteNode){
        DeleteNode->parent->left = Sentinel;
      }
      else if (DeleteNode->parent->right == DeleteNode){
        DeleteNode->parent->right = Sentinel;
      }
      delete DeleteNode;
    }
  }
  else {}
  return 1;
}
// Returns Maximum node
RBbst::node * RBbst::maximum_node(node *&n){
    node * Temp = n;
    //check if node is not a sentinel
    if (Temp != Sentinel){
      //while right child is not a sentinel go right
      while (Temp->right != Sentinel){
        Temp = Temp->right;
      }
      return Temp;
    }
}
// Deleting Case 1
void RBbst::delete_case1(node *&child, node *& n){
  //if nodes parent is sentinel, nothing to do
  if (child->parent != Sentinel){
    delete_case2(child, n);
  }
}
// Deleting Case 2
void RBbst::delete_case2(node *&child, node *& n){
  //if the sibling of the node is red
  if (node_colour(sibling(child)) == RED){
    //colour swap nodes parent and sibling
    child->parent->colour = RED;
    sibling(child)->colour = BLACK;
    //if node is left child
    if (child == child->parent->left){
      //rotate left
      rotate_left(child->parent, root);
    }
    //otherwise rotate right
    else {
      rotate_right(child->parent, root);
    }
  }
  //otherwise delete case 3
  delete_case3(child, n);
}
// Deleting Case 3
void RBbst::delete_case3(node *&child, node *& n){
  //if nodes parent is black, nodes sibling is black, nodes neice and nephew are black
  if (node_colour(child->parent) == BLACK && node_colour(sibling(child)) == BLACK &&
  node_colour(sibling(child)->left) == BLACK && node_colour(sibling(child)->right) == BLACK){
    //set siblings colour to red
    sibling(child)->colour = RED;
    //delete case 1
    delete_case1(child->parent, n);
  }
  //otherwise delete case 4
  else {
    delete_case4(child, n);
  }
}
// Deleting Case 4
void RBbst::delete_case4(node *&child, node *& n){
  //if nodes parent is red, sibling is black, neice and nephew are black
  if (node_colour(child->parent) == RED && node_colour(sibling(child)) == BLACK &&
  node_colour(sibling(child)->left) == BLACK && node_colour(sibling(child)->right) == BLACK){
    //set siblings colour to red and parent to black
    sibling(child)->colour = RED;
    child->parent->colour = BLACK;
  }
  //otherwise delete case 5
  else {
    delete_case5(child, n);
  }
}
// Deleting Case 5
void RBbst::delete_case5(node *&child, node *& n){
  if (node_colour(sibling(child))== BLACK){
    //if node is a left child and sibling is black, neice is red and nephew is black
    if (child == child->parent->left && node_colour(sibling(child)->left) == RED
        && node_colour(sibling(child)->right) == BLACK){
      //change sibling to red and neice to black
      sibling(child)->colour = RED;
      sibling(child)->left->colour = BLACK;
      //rotate right
      rotate_right(sibling(child)->left, n);
    }
    //otherwise if node is right child, sibling is black, nephew is red and neice is black
    else if (child == child->parent->right && node_colour(sibling(child)->right) == RED
             && node_colour(sibling(child)->left) == BLACK){
      //change sibling to red and nephew to black
      sibling(child)->colour = RED;
      sibling(child)->right->colour = BLACK;
      //rotate left
      rotate_left(sibling(child)->right, n);
    }
  }
  //otherwise delete case 6
  delete_case6(child, n);
}
// Deleting Case 6
void RBbst::delete_case6(node *&child, node *& n){
  //set siblings colour to parents colour
  sibling(child)->colour = node_colour(child->parent);
  //set parent to black
  child->parent->colour = BLACK;
  //if node is left child
  if (child == child->parent->left){
    //set nephew to black
    sibling(child)->right->colour = BLACK;
    //rotate left
    rotate_left(sibling(child), n);
  }
  //otherwise
  else{
    //set neice to black
    sibling(child)->left->colour = BLACK;
    //rotate right
    rotate_right(sibling(child), n);
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
  verify_property_3(n->left);
  //verify property 4 on right child
  verify_property_3(n->right);
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
void RBbst::swapElements(node *& n, node *& m){
  //transfer information from first node to temp
  node * temp = new node;
  temp->data = n->data;
  temp->key = n->key;
  //transfer information from second node to first
  n->data = m->data;
  n->key= m->key;
  //transfer information from temp to second
  m->data = temp->data;
  m->key= temp->key;
  delete temp;
}
