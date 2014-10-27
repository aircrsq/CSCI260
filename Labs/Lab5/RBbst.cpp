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
  temp=Find(n,key,0);
  //attach the new node to the find
  current->parent=temp;
  //if node is not a sentinel
  if (n != Sentinel){
    //if new node is greater than parent
    if(key>=temp->key){
      //make right child
      temp->right=current;
    }
    //otherwise
    else{
      //make left child
      temp->left=current;
    }
  }
  //check the insert for case 1
  insert_case1(current,n);
}
//return a pointer to the node whose key value is key
RBbst::node * RBbst::Find(node *&n,int key,int i){
  node * temp = Sentinel;
  //if empty tree, return node
  if(n == Sentinel){
    return n;
  }
  //if key is equal to node key, return node
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
      return Find(n->left,key,i);
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
      return Find(n->right,key,i);
    }
  }
}
//root must be black
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
//then check insert case for grandparent
void RBbst::insert_case3(node *&current, node *&n){
  node *u = uncle(current);
  node *g = grandparent(current);
  //if uncle is red
  if ((u->colour == RED) && (u != Sentinel)) {
    //colour swap parent, uncle, and grandparent
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
//uncle is black, child is left of right or right of left
void RBbst::insert_case4(node *&current, node *&n){
  node *g = grandparent(current);
    //if current is right child and parent is left child
  if ((current == current->parent->right) && (current->parent == g->left)) {
    //rotate left right
    rotate_left(current,n);
    //change current for second rotate
    current = current->left;
  }
  //otherwise if current is left child and parent is right
  else if ((current == current->parent->left) && (current->parent == g->right)) {
    //rotate right left
    rotate_right(current,n);
    //change current for second rotate
    current = current->right;
  }
  //check case 5
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
    //rotate right on parent
    rotate_right(current->parent,n);
  }
  //otherwise child is right of right
  else{
    //rotate left on parent
    rotate_left(current->parent,n);
  }
}
//return a pointer to uncle
RBbst::node * RBbst::uncle(node *&current){
  node *g = grandparent(current);
  //if grandparent is sentinel, uncle is sentinel
  if (g == Sentinel){
    return Sentinel;
  }
  //if parent is left then uncle is right
  if (current->parent == g->left){
    return g->right;
  }
  //otherwise uncle is left
  else{
    return g->left;
  }
}
//return a pointer to grandparent
RBbst::node * RBbst::grandparent(node *&current){
  //if current and parent are not sentinels, return grandparent
  if ((current != Sentinel) && (current->parent != Sentinel)){
    return current->parent->parent;
  }
  //otherwise return sentinel
  else{
    return Sentinel;
  }
}
// Return Sibling of Node
RBbst::node * RBbst::sibling(node *&current){
  //check that node and nodes parent are not sentinel
  if (current != Sentinel){
    if (current->parent != Sentinel){
      //if current is left child
      if (current == current->parent->left){
        //return right child
        return current->parent->right;
      }
      //otherwise
      else{
        //return left child
        return current->parent->left;
      }
    }
  }
}
//rotate node to left
void RBbst::rotate_left(node *current, node *n){
  //set up pointers
  node *GP = grandparent(current);
  node *P = current->parent;
  node *C = current;
  node *CR = current->right;
  node *CL = current->left;
  //demote parent to child's child
  P->parent = current;
  //promote current to parent
  current->parent = GP;
  //attach currents left to parents right
  P->right = CL;
  //point currents left to parent
  current->left = P;
  //if the parent is a sentinel
  if (current->parent == Sentinel){
    //then current is new root
    root=current;
  }
  //if grandparent is not sentinel
  if (GP != Sentinel){
    //and parent is grandparents left child
    if (GP->left == P){
      //make current grandparents left child
      GP->left = current;
    }
    //otherwise
    else{
      //make current grandparents right child
      GP->right = current;
    }
  }
}
//rotate node to right
void RBbst::rotate_right(node *current, node *n){
  //set up pointers
  node *GP = grandparent(current);
  node *P = current->parent;
  node *C = current;
  node *CR = current->right;
  node *CL = current->left;
  //demote parent to child's child
  P->parent = current;
  //promote current to parent
  current->parent = grandparent(current);
  //attach currents right to parents left
  P->left = current->right;
  //point currents right to parent
  current->right = P;
  //if the parent is a sentinel
  if (current->parent == Sentinel){
    //then current is new root
    root=current;
  }
  //if grandparent is not sentinel
  if (GP != Sentinel){
    //and parent is grandparents left child
    if (GP->left == P){
      //make current grandparents left child
      GP->left = current;
    }
    else{
      //make current grandparents right child
      GP->right = current;
    }
  }
}

// find the node with key and return data
string RBbst::search(int key, node *&current){
  // if empty tree
  if (current == Sentinel){
    return "nothing in tree \n";
  }
  // otherwise if nodes key is > than k
  else if (key < current->key){
    //recurse down left subtree
    return search(key, current->left);
  }
  // otherwise if nodes key is < k
  else if (key > current->key){
    //recurse down right subtree
    return search(key, current->right);
  }
  // otherwise return data
  else{
    return current->data;
  }
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
   if (current == Sentinel) {
     return;
   }
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
   if (current->left != Sentinel){
     PreOrdprint(current->left);
   }
   //print right tree
   if (current->right != Sentinel){
     PreOrdprint(current->right);
   }
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
     if (current->left->key != -99999999){
       cout << current->left->key;
     }
     else{
       cout << "Sentinel";
     }
     cout << "<-left,right->";
     if (current->right->key != -99999999){
       cout << current->right->key;
     }
     else{
       cout << "Sentinel";
     }
     cout << ") ";
   }
   //print left tree
   if (current->left != Sentinel){
     //recurse down left subtree
     debugprint(current->left);
   }
   //print right tree
   if (current->right != Sentinel){
     //recurse down right subtree
     debugprint(current->right);
   }
}
// if the subtree rooted at n contains a node whose key
// matches k then remove it from the subtree
bool RBbst::deleteElement(int key, node *&n){
  node * child = Sentinel;
  node * predecessor;
  //Find the node to delete
  node * DeleteNode = Find(n,key,0);
  //if there is a left subtree,
  if (DeleteNode->left != Sentinel){
    //search for a predecessor starting at the left child
    predecessor = maximum_node(DeleteNode->left);
  }
  //otherwise no predecessor exists
  else {
    predecessor = Sentinel;
  }
  //if left subtree exists on predecessor
  if (predecessor->left != Sentinel){
    //make it child
    child = predecessor->left;
  }
  //otherwise
  else{
    //set child to sentinel
    child = Sentinel;
  }
  //if predecessor is valid
  if (predecessor != Sentinel){
    //swap the key and data
    swapElements(DeleteNode, predecessor);
    //if node predecessor is red,
    if (node_colour(predecessor) == RED){
      //if left child is not sentinel
      if (predecessor->left != Sentinel){
        //attach left child to parent
        predecessor->parent->left = predecessor->left;
      }
      //otherwise
      else if (predecessor->left == Sentinel){
        //attach sentinel to left child
        predecessor->parent->left = Sentinel;
      }
    }
    //if colour is black,
    else if (node_colour(predecessor) == BLACK){
      //if child is red
      if (child->colour == RED){
        //set to colour of child to black
        child->colour = BLACK;
        //attach grandparents right to child
        predecessor->parent->right = child;
        //attach child to grandparents right
        child->parent = predecessor->parent;
      }
      //otherwise is child is not sentinel
      else if (child != Sentinel){
        //check delete case 1 with child
        delete_case1(child, root);
      }
      //otherwise
      else {
        //check delete case 1 with predesessor
        delete_case1(predecessor, n);
        //delete predecessor
        delete predecessor;
      }
    }
  }
  //if predecessor is Sentinel
  else if (predecessor == Sentinel){
    //if node colour is black
    if (DeleteNode->colour == BLACK){
      //check delete case 1 with delete node
      delete_case1(DeleteNode, n);
      //if delete node is left child
      if (DeleteNode->parent->left == DeleteNode){
        //attach sentinel to parents left
        DeleteNode->parent->left = DeleteNode->right;
      }
      //otherwise delete node is right child
      else if (DeleteNode->parent->right == DeleteNode){
        //attach delete nodes left child to parents right
        DeleteNode->parent->right = DeleteNode->left;
      }
      //delete delete node
      delete DeleteNode;
    }
    //otherwise the node colour is red
    else {
      //if delete node is left child
      if (DeleteNode->parent->left == DeleteNode){
        //attach sentinel to parents left
        DeleteNode->parent->left = DeleteNode->right;
      }
      //otherwise delete node is right child
      else if (DeleteNode->parent->right == DeleteNode){
        //attach sentinel to parents right
        DeleteNode->parent->right = DeleteNode->left;
      }
      //delete delete node
      delete DeleteNode;
    }
  }
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
//Delete Case 1
void RBbst::delete_case1(node *&child, node *& n){
  //if nodes parent is sentinel,
  if (child->parent == Sentinel){
    //nothing to do
    return;
  }
  //otherwise
  else if (child->parent != Sentinel){
    //check delete case 2
    delete_case2(child, n);
  }
}
//Delete Case 2
void RBbst::delete_case2(node *&child, node *& n){
  //if the sibling of the node is red
  if (node_colour(sibling(child)) == RED){
    //colour swap nodes parent and sibling
    child->parent->colour = RED;
    sibling(child)->colour = BLACK;
    //if node is left child
    if (child == child->parent->left){
      //rotate left on parent
      rotate_left(child->parent, root);
    }
    //otherwise node is right child
    else {
      //rotate right on parent
      rotate_right(child->parent, root);
    }
  }
  //otherwise check delete case 3
  delete_case3(child, n);
}
// Deleting Case 3
void RBbst::delete_case3(node *&child, node *& n){
  //if nodes parent is black, nodes sibling is black, nodes neice and nephew are black
  if (node_colour(child->parent) == BLACK && node_colour(sibling(child)) == BLACK &&
  node_colour(sibling(child)->left) == BLACK && node_colour(sibling(child)->right) == BLACK){
    //set siblings colour to red
    sibling(child)->colour = RED;
    //check delete case 1 on parent
    delete_case1(child->parent, n);
  }
  //otherwise
  else {
    //check delete case 4 on child
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
  //otherwise
  else {
    //check delete case 5
    delete_case5(child, n);
  }
}
// Deleting Case 5
void RBbst::delete_case5(node *&child, node *& n){
  //if sibling is black
  if (node_colour(sibling(child))== BLACK){
    //if node is a left child and neice is red and nephew is black
    if (child == child->parent->left && node_colour(sibling(child)->left) == RED
        && node_colour(sibling(child)->right) == BLACK){
      //change sibling to red and neice to black
      sibling(child)->colour = RED;
      sibling(child)->left->colour = BLACK;
      //rotate right on sibling
      rotate_right(sibling(child)->left, n);
    }
    //otherwise if node is right child, nephew is red and neice is black
    else if (child == child->parent->right && node_colour(sibling(child)->right) == RED
             && node_colour(sibling(child)->left) == BLACK){
      //change sibling to red and nephew to black
      sibling(child)->colour = RED;
      sibling(child)->right->colour = BLACK;
      //rotate left on sibling
      rotate_left(sibling(child)->right, n);
    }
  }
  //check delete case 6
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
    //rotate left on sibling
    rotate_left(sibling(child), n);
  }
  //otherwise
  else{
    //set neice to black
    sibling(child)->left->colour = BLACK;
    //rotate right on sibling
    rotate_right(sibling(child), n);
  }
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
