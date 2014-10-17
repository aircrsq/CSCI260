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
#include <assert.h>
#include "RBbst.h"
using namespace std;

/*
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         int colour;
  }; *root;   */

// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
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
    if(key>=temp->key)
      temp->right=current;
    //otherwise new node is left child
    else temp->left=current;
  }
  //check the insert for case 1
  n=insert_case1(current,n);
  return n;
}

RBbst::node * RBbst::finding(node *&n,int key,int i){
  node * temp = Sentinel;
  //if empty node, return node
  if(n == Sentinel)return n;
  if(i == 1)return temp;
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
    else
      return finding(n->left,key,i);
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

RBbst::node * RBbst::insert_case1(node *&n, node *&head){
  //if parent is a Sentinel, than node is root and must be black
  if (n->parent == Sentinel)
    n->colour = BLACK;
  //otherwise check case 2
  else
    head=insert_case2(n,head);
  return head;
}

RBbst::node * RBbst::insert_case2(node *&n, node *&head){
  if (n->parent->colour == BLACK)
    return head;
  else
    head=insert_case3(n,head);
  return head;
}

RBbst::node * RBbst::insert_case3(node *&n, node *&head){
  node *u = uncle(n), *g;
  if ((u != Sentinel) && (u->colour == RED)) {
    n->parent->colour = BLACK;
    u->colour = BLACK;
    g = grandparent(n);
    g->colour = RED;
    head=insert_case1(g,head);
  }
  else {
    head=insert_case4(n,head);
  }
  return head;
}

RBbst::node * RBbst::insert_case4(node *&n, node *&head){
  node *g = grandparent(n);
  if ((n == n->parent->right) && (n->parent == g->left)) {
    head=rotate_left(n->parent,head);
    n = n->left;
  }
  else if ((n == n->parent->left) && (n->parent == g->right)) {
    head=rotate_right(n->parent,head);
    n = n->right;
  }
  head=insert_case5(n,head);
  return head;
}

RBbst::node * RBbst::insert_case5(node *&n, node *&head){
  node *g = grandparent(n);
  n->parent->colour = BLACK;
  g->colour = RED;
  if (n == n->parent->left)
    head=rotate_right(n,head);
  else
    head=rotate_left(n,head);
  return head;
}

RBbst::node * RBbst::uncle(node *&n){
  node *g = grandparent(n);
  if (g == Sentinel)
    return Sentinel;
  if (n->parent == g->left)
    return g->right;
  else
    return g->left;
}

RBbst::node * RBbst::grandparent(node *&n){
  if ((n != Sentinel) && (n->parent != Sentinel))
    return n->parent->parent;
  else
    return Sentinel;
}

RBbst::node * RBbst::rotate_left(node *n, node *head){
  node *g = grandparent(n);
  node *saved_p=g->parent;
  node *saved_left_n=n->parent->left;
  n->parent->left=g;
  g->right=saved_left_n;
  n->parent->parent=saved_p;
  g->parent=n->parent;
  if(saved_p!=Sentinel){
    if(saved_p->left==g){
      saved_p->left=n->parent->parent;
    }
    else if(saved_p->right==g){
      saved_p->right=n->parent->parent;
    }
  }
  else head=n->parent;
  return head;
}

RBbst::node * RBbst::rotate_right(node *n, node *head){
  node *g = grandparent(n);
  node *saved_p=g->parent;
  node *saved_right_p=n->parent->right;
  n->parent->right=g;
  g->left=saved_right_p;
  n->parent->parent=saved_p;
  g->parent=n->parent;
  if(saved_p!=Sentinel){
    if(saved_p->left==g){
      saved_p->left=n->parent->parent;
    }
    else if(saved_p->right==g){
      saved_p->right=n->parent->parent;
    }
  }
  else head=n->parent;
  return head;
}

// find the node with key
// return data
string RBbst::search(int key, node *&n){
  // if empty tree
  if (n == Sentinel) return "nothing";
  // otherwise if nodes key is > than k
  else if (key < n->key){
    return search(key, n->left);
  }
  // otherwise if nodes key is < k
  else if (key > n->key){
    return search(key, n->right);
  }
  // otherwise return data
  else
    return n->data;
}

// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
//2:c (5 b N N)
//5:a (N b 2 7)
//7:b (5 b N N)
void RBbst::print(node *&n){
   int c = n->colour;
   char C;
   if (c == 1){C = 'b';}
   else C = 'r';
   if (n == Sentinel) return;
   if (n->left != Sentinel) print(n->left);
   if (n->parent == Sentinel){
     cout << n->key << ":" << n->data << " (" << "N " << C << " "
          << n->left->key << " " << n->right->key << ")" << endl;
   }
   else if (n->parent != Sentinel){
     if ((n->left == Sentinel) && (n->right == Sentinel)){
       cout << n->key << ":" << n->data << " (" << n->key << " " << C
          << " " << "N " << "N" << ")" << endl;
     }
     else if ((n->left == Sentinel) && (n->right != Sentinel)){
       cout << n->key << ":" << n->data << " (" << n->key << " " << C
          << " " << "N " << n->right->key << ")" << endl;
     }
     else if ((n->left != Sentinel) && (n->right == Sentinel)){
       cout << n->key << ":" << n->data << " (" << n->key << " " << C
          << " " << n->left->key << " N" << ")" << endl;
     }
     else {
     cout << n->key << ":" << n->data << " (" << n->key << " " << C
          << " " << n->left->key << " " << n->right->key << ")" << endl;
     }
   }
   if (n->right != Sentinel) print(n->right);
}

//Change to printout as specified in Lab5 Preorder Print
void RBbst::PreOrdprint(node *&n){
   int c = n->colour;
   char C;
   if (c == 1){C = 'b';}
   else C = 'r';
   if (n == Sentinel) return;
   cout << n->key << ":" << n->data << " " << C << " (";
   if (n->left != Sentinel) cout << n->left->key;
   else cout << "N";
   cout << "<- " << n->key << " ->";
   if (n->right != Sentinel) cout << n->right->key;
   else cout << "N";
   cout << ") " << endl;

   if (n->left != Sentinel) PreOrdprint(n->left);
   if (n->right != Sentinel) PreOrdprint(n->right);
   return;
}

// display the contents and structure of the subtree rooted at n,
// performed via preorder traversal
void RBbst::debugprint(node *&n){
   if (n == Sentinel) return;
   cout << n->key << ":" << n->data << " (";
   if (n->left->key != -99999999) cout << n->left->key;
   else cout << "Sentinel";
   cout << "<-left,right->";
   if (n->right->key != -99999999) cout << n->right->key;
   else cout << "Sentinel";
   cout << ") ";

   if (n->left != Sentinel) debugprint(n->left);
   if (n->right != Sentinel) debugprint(n->right);
}

// if the subtree rooted at n contains a node whose key
// matches k then remove it from the subtree, and return true,
// otherwise return
bool RBbst::deleteElement(int key, node *&root){
  node* child;
  node* n = finding(root,key,0);
  if (n == Sentinel)
    return 0;
  if (n->left != Sentinel && n->right != Sentinel){
    node* pred = maximum_node(n->left);
    n->key = pred->key;
    n->data = pred->data;
    n = pred;
  }
  assert(n->left == Sentinel || n->right == Sentinel);
  child = n->right == Sentinel ? n->left  : n->right;
  if (node_colour(n) == BLACK){
    n->colour = node_colour(child);
    delete_case1(root, n);
  }
  replace_node(root, n, child);
  delete n;
  verify_properties(root);
  return 1;
}

// Replace a node
void RBbst::replace_node(node *&root, node *&n, node *&child){
    if (n->parent == Sentinel){
        root = child;
    }
    else{
        if (n == n->parent->left)
            n->parent->left = child;
        else
            n->parent->right = child;
    }
    if (child != Sentinel){
        child->parent = n->parent;
    }
}

// Returns Maximum node
RBbst::node * RBbst::maximum_node(node *&n){
    assert (n != Sentinel);
    while (n->right != Sentinel){
        n = n->right;
    }
    return n;
}

// Deleting Case 1
void RBbst::delete_case1(node *& root, node *&n){
  if (n->parent == Sentinel)
    return;
  else
    delete_case2(root, n);
}

// Deleting Case 2
void RBbst::delete_case2(node *& root, node *&n){
  if (node_colour(sibling(n)) == RED){
    n->parent->colour = RED;
    sibling(n)->colour = BLACK;
    if (n == n->parent->left)
      rotate_left(root, n->parent);
    else
      rotate_right(root, n->parent);
  }
  delete_case3(root, n);
}

// Deleting Case 3
void RBbst::delete_case3(node *& root, node *&n){
  if (node_colour(n->parent) == BLACK && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->left) == BLACK && node_colour(sibling(n)->right) == BLACK){
    sibling(n)->colour = RED;
    delete_case1(root, n->parent);
  }
  else
    delete_case4(root, n);
}

// Deleting Case 4
void RBbst::delete_case4(node *& root, node *&n){
  if (node_colour(n->parent) == RED && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->left) == BLACK && node_colour(sibling(n)->right) == BLACK){
    sibling(n)->colour = RED;
    n->parent->colour = BLACK;
  }
  else
    delete_case5(root, n);
}

// Deleting Case 5
void RBbst::delete_case5(node *& root, node *&n){
  if (n == n->parent->left && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->left) == RED && node_colour(sibling(n)->right) == BLACK){
    sibling(n)->colour = RED;
    sibling(n)->left->colour = BLACK;
    rotate_right(root, sibling(n));
  }
  else if (n == n->parent->right && node_colour(sibling(n)) == BLACK &&
  node_colour(sibling(n)->right) == RED && node_colour(sibling(n)->left) == BLACK){
    sibling(n)->colour = RED;
    sibling(n)->right->colour = BLACK;
    rotate_left(root, sibling(n));
  }
  delete_case6(root, n);
}

// Deleting Case 6
void RBbst::delete_case6(node *& root, node *&n){
  sibling(n)->colour = node_colour(n->parent);
  n->parent->colour = BLACK;
  if (n == n->parent->left){
    assert (node_colour(sibling(n)->right) == RED);
    sibling(n)->right->colour = BLACK;
    rotate_left(root, n->parent);
  }
  else{
    assert (node_colour(sibling(n)->left) == RED);
    sibling(n)->left->colour = BLACK;
    rotate_right(root, n->parent);
  }
}

// Return Sibling of Node
RBbst::node * RBbst::sibling(node *&n){
    assert (n != Sentinel);
    assert (n->parent != Sentinel);
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

// Verifying Properties of Red black Tree
void RBbst::verify_properties(node *&n){
    verify_property_1 (n);
    verify_property_2 (n);
    verify_property_3 (n);
    verify_property_4 (n);
}

// Verifying Property 1 Each node must be red or black
void RBbst::verify_property_1(node *&n){
    assert (node_colour(n) == RED || node_colour(n) == BLACK);
    if (n == Sentinel)
        return;
    verify_property_1(n->left);
    verify_property_1(n->right);
}

// Verifying Property 2 Root node must be black
void RBbst::verify_property_2(node *&n){
    assert (node_colour(n) == BLACK);
}

// Verifying Property 3 If a node is red, it's children and parent must be black
void RBbst::verify_property_3(node *&n){
    if (node_colour(n) == RED){
        assert (node_colour(n->left) == BLACK);
        assert (node_colour(n->right) == BLACK);
        assert (node_colour(n->parent) == BLACK);
    }
    if (n == Sentinel)
        return;
    verify_property_4(n->left);
    verify_property_4(n->right);
}

// Verifying Property 4 The Black height must be the same for all leaves
void RBbst::verify_property_4(node *&n){
    int black_count_path = -1;
    verify_property_4_helper(n, 0, &black_count_path);
}

void RBbst::verify_property_4_helper(node *&n, int black_count, int* path_black_count){
    if (node_colour(n) == BLACK){
        black_count++;
    }
    if (n == Sentinel){
        if (*path_black_count == -1){
            *path_black_count = black_count;
        }
        else {
            assert (black_count == *path_black_count);
        }
        return;
    }
    verify_property_4_helper(n->left,  black_count, path_black_count);
    verify_property_4_helper(n->right, black_count, path_black_count);
}

 //Returns colour of a node
int RBbst::node_colour(node *n){
  return n->colour;
    //return n->colour == Sentinel ? BLACK : n->colour;
}

// delete all nodes in the subtree rooted at n,
// and set n to null
void RBbst::deallocate(node* &n){
   if (n == Sentinel) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = Sentinel;
}
/*
// swap data and key between two nodes
void RBbst::swapElements(node* n, node* m){
   node temp;
   temp.data = n->data;
   n->data = m->data;
   m->data = temp.data;

   temp.key = n->key;
   n->key= m->key;
   m->key= temp.key;
}	*/
