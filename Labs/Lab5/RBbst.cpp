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
  node* current= new node;
  current->key = key;
  current->data=data;
  current->left=NO_NODE;
  current->right=NO_NODE;
  current->colour=RED;
  current->parent=NO_NODE;
  if(n==NO_NODE){
    current->colour=BLACK;
    n=current;
    return n;
  }
  else{
    node * temp = new node;
    temp=finding(n,key,0);
    current->parent=temp;
    if(key>=temp->key)
      temp->right=current;
    else temp->left=current;
  }
  n=insert_case1(current,n);
  return n;
}

RBbst::node * RBbst::finding(node *&n,int key,int i){
  //static int i;
  node * temp = NO_NODE;
  if(n == NO_NODE)return NO_NODE;
  if(i == 1)return temp;
  if(n->key > key){
    if(n->left==NO_NODE){
      temp=n;
      i=1;
      return temp;
    }
    finding(n->left,key,i);
  }
  else{
    if(n->right==NO_NODE){
      temp=n;
      i=1;
      return temp;
    }
    finding(n->right,key,i);
  }						
  return temp;
}

RBbst::node * RBbst::insert_case1(node *&n, node *&head){
  if (n->parent == NO_NODE)
    n->colour = BLACK;
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
  if ((u != NO_NODE) && (u->colour == RED)) {
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
  if (g == NO_NODE)
    return NO_NODE;
  if (n->parent == g->left)
    return g->right;
  else
    return g->left;
}

RBbst::node * RBbst::grandparent(node *&n){
  if ((n != NO_NODE) && (n->parent != NO_NODE))
    return n->parent->parent;
  else
    return NO_NODE;
}

RBbst::node * RBbst::rotate_left(node *n, node *head){
  node *g = grandparent(n);
  node *saved_p=g->parent;
  node *saved_left_n=n->parent->left;
  n->parent->left=g;
  g->right=saved_left_n;
  n->parent->parent=saved_p;
  g->parent=n->parent;
  if(saved_p!=NO_NODE){
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
  if(saved_p!=NO_NODE){
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
  if (n == NO_NODE) return "nothing";
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
   if (n == NO_NODE) return;
   if (n->left != NO_NODE) print(n->left);
   if (n->parent == NO_NODE){
     cout << n->key << ":" << n->data << " (" << "N " << C << " "
          << n->left->key << " " << n->right->key << ")" << endl;
   }
/*   else if (n->parent != NO_NODE){
     cout << n->key << ":" << n->data << " (" << n->key << " " << C
          << " " << n->left->key << " " << n->right->key << ")" << endl;
   }
*/   if (n->right != NO_NODE) print(n->right);
}

//Change to printout as specified in Lab5 Preorder Print
void RBbst::PreOrdprint(node *&n){
   int c = n->colour;
   char C;
   if (c == 1){C = 'b';}
   else C = 'r';
   if (n == NO_NODE) return;
   cout << n->key << ":" << n->data << " " << C << " (";
   if (n->left != NO_NODE) cout << n->left->key;
   else cout << "N";
   cout << "<- " << n->key << " ->";
   if (n->right != NO_NODE) cout << n->right->key;
   else cout << "N";
   cout << ") " << endl;

   if (n->left != NO_NODE) PreOrdprint(n->left);
   if (n->right != NO_NODE) PreOrdprint(n->right);
   return;
}

// display the contents and structure of the subtree rooted at n,
// performed via preorder traversal
void RBbst::debugprint(node *&n){
   if (n == NO_NODE) return;
   cout << n->key << ":" << n->data << " (";
   if (n->left) cout << n->left->key;
   else cout << "NO_NODE";
   cout << "<-left,right->";
   if (n->right) cout << n->right->key;
   else cout << "NO_NODE";
   cout << ") ";

   if (n->left != NO_NODE) debugprint(n->left);
   if (n->right != NO_NODE) debugprint(n->right);
}

// if the subtree rooted at n contains a node whose key
// matches k then remove it from the subtree, and return true,
// otherwise return
bool RBbst::deleteElement(int key, node *&root){
  node* child;
  node* n = finding(root,key,0);
  if (n == NO_NODE)
    return 0;
  if (n->left != NO_NODE && n->right != NO_NODE){
    node* pred = maximum_node(n->left);
    n->key = pred->key;
    n->data = pred->data;
    n = pred;
  }
  assert(n->left == NO_NODE || n->right == NO_NODE);
  child = n->right == NO_NODE ? n->left  : n->right;
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
    if (n->parent == NO_NODE){
        root = child;
    }
    else{
        if (n == n->parent->left)
            n->parent->left = child;
        else
            n->parent->right = child;
    }
    if (child != NO_NODE){
        child->parent = n->parent;
    }
}

// Returns Maximum node
RBbst::node * RBbst::maximum_node(node *&n){
    assert (n != NO_NODE);
    while (n->right != NO_NODE){
        n = n->right;
    }
    return n;
}

// Deleting Case 1
void RBbst::delete_case1(node *& root, node *&n){
  if (n->parent == NO_NODE)
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
    assert (n != NO_NODE);
    assert (n->parent != NO_NODE);
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
    if (n == NO_NODE)
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
    if (n == NO_NODE)
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
    if (n == NO_NODE){
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
    //return n->colour == NO_NODE ? BLACK : n->colour;
}

// delete all nodes in the subtree rooted at n,
// and set n to null
void RBbst::deallocate(node* &n){
   if (n == NO_NODE) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = NO_NODE;
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
