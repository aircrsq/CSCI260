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
#include "RBbst.h"
using namespace std;

/*
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         int colour;
  };
  */

// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
RBbst::node * RBbst::insert(int key, string data, node *&root){
 /*****************************************************/
  node* current= new node;
  current->key = key;
  current->data=data;
  current->left=NULL;
  current->right=NULL;
  current->colour=RED;
  if(root==NULL){
    current->colour=BLACK;
    current->parent=NULL;
    root=current;
    return root;
  }
  else{
    node*temp=NULL;
    temp=finding(root,key,0);
    current->parent=temp;
    if(key>=temp->key)
      temp->right=current;
    else temp->left=current;
  }
  root=insert_case1(current,root);
  return root;

 /*************************************
  node *inserted_node = new_node(key, data, r, NO_NODE, NO_NODE);
  if (n == NO_NODE){
    n = inserted_node;
  }
  else{
    node *r = n;
    while (1){
      if (n->key < k) {
        if (r->right == NO_NODE){
          r->right = inserted_node;
          break;
        }
        else{
          r = r->right;
        }
      }
      else if (n->key > k){
        if (r->left == NO_NODE){
          r->left = inserted_node;
          break;
        }
        else{
          r = r->left;
        }
      }
      else{
        r->data = data;
        return;
      }
    }
    inserted_node->parent = n;
  }
  insert_case1(n, inserted_node);
  verify_properties(n); */
}

RBbst::node * finding(node*& root,int key,int i){
  //static int i;
  static  node* temp=NULL;
  if(root==NULL)return NULL;
  if(i==1)return temp;
  if(root->key>key){
    if(root->left==NULL){
      temp=root;i=1;return temp;
    }
    finding(root->left,key,i);
  }
  else{
    if(root->right==NULL){
      temp=root;
      i=1;
      return temp;
    }
    finding(root->right,key,i);
  }
  return temp;
}

RBbst::node * insert_case1(node *&n, node *&head){
  if (n->parent == NULL)
    n->colour = BLACK;
  else
    head=insert_case2(n,head);
  return head;
}

RBbst::node * insert_case2( node *&n, node *head){
  if (n->parent->colour == BLACK)
    return head;
  else
    head=insert_case3(n,head);
  return head;
}

RBbst::node * insert_case3( node *&n, node *&head){
  node *u = uncle(n), *g;
  if ((u != NULL) && (u->colour == RED)) {
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

RBbst::node * insert_case4(node *&n, node *&head){
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

RBbst::node * insert_case5(node *&n, node *&head){
  node *g = grandparent(n);
  n->parent->colour = BLACK;
  g->colour = RED;
  if (n == n->parent->left)
    head=rotate_right(n,head);
  else
    head=rotate_left(n,head);
  return head;
}

RBbst::node * uncle(node *&n){
  node *g = grandparent(n);
  if (g == NULL)
    return NULL; // No grandparent means no uncle
  if (n->parent == g->left)
    return g->right;
  else
    return g->left;
}

RBbst::node * grandparent(node *&n){
  if ((n != NULL) && (n->parent != NULL))
    return n->parent->parent;
  else
    return NULL;
}

RBbst::node * rotate_left(node *&n, node *&head){
  node *g = grandparent(n);
  node *saved_p=g->parent;
  node *saved_left_n=n->parent->left;
  n->parent->left=g;
  g->right=saved_left_n;
  n->parent->parent=saved_p;
  g->parent=n->parent;
  if(saved_p!=NULL){
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

RBbst::node * rotate_right(node *&n, node *&head){
  node *g = grandparent(n);
  node *saved_p=g->parent;
  node *saved_right_p=n->parent->right;
  n->parent->right=g;
  g->left=saved_right_p;
  n->parent->parent=saved_p;
  g->parent=n->parent;
  if(saved_p!=NULL){
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
string RBbst::search(int key, node *&root){
  // if empty tree
  if (root == NO_NODE) return "nothing";
  // otherwise if nodes key is > than k
  else if (key < root->key){
    return search(k, root->left);
  }
  // otherwise if nodes key is < k
  else if (key > root->key){
    return search(key, root->right);
  }
  // otherwise return data
  else
    return root->data;
}

// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
/*2:c (5 b N N)
5:a (N b 2 7)
7:b (5 b N N)	*/
void RBbst::print(node *&n){
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
void RBbst::debugprint(node *&n){
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

//Change to printout as specified in Lab5 Preorder Print
void RBbst::PreOrdprint(node *&n){
   if (n == NO_NODE) return;
   cout << n->key << ":" << n->data << " (";
   if (n->left) cout << n->left->key;
   else cout << "NULL";
   cout << "<-left,right->";
   if (n->right) cout << n->right->key;
   else cout << "NULL";
   cout << ") ";

   PreOrdprint(n->left);
   PreOrdprint(n->right);
}

// if the subtree rooted at n contains a node whose key
// matches k then remove it from the subtree, and return true,
// otherwise return
bool RBbst::deleteElement(int key, node *&root){
  node* child;
  node* n = finding(root,key,0);
  if (n == NO_NODE)
    return;
  if (n->left != NO_NODE && n->right != NO_NODE){
    node* pred = maximum_node(n->left);
    n->key = pred->key;
    n->value = pred->value;
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
  verify_properties(t);
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
    n->parent->coluor = RED;
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
    rotate_right(t, sibling(n));
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
RBbst::node* RBbst::sibling(node *&n){
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
    assert (node_colour(n) == RED || node_colour(n) == BLACK);  //confirm node_color***********
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
    verify_property_5_helper(n, 0, &black_count_path);
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
 int RBbst::node_colour(node *&n){
    return n == NO_NODE ? BLACK : n->colour;
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


/*************************************************/

/*
// Return grandparent
RBbst::node* RBbst::grandparent(node *&n){
    assert (n != NO_NODE);
    assert (n->parent != NO_NODE);
    assert (n->parent->parent != NO_NODE);
    return n->parent->parent;
}

 // Return Uncle of Node
RBbst::node* RBbst::uncle(node *&n){
    assert (n != NO_NODE);
    assert (n->parent != NO_NODE);
    assert (n->parent->parent != NO_NODE);
    return sibling(n->parent);
}

// Create Red Black Tree
RBbst::node* RBbst::rbtree_create(){
    rbtree t = new rbtree_t;
    t->root = NO_NODE;
    verify_properties(t);
    return t;
}
// Creating New Node of Reb Black Tree
RBbst::node* RBbst::new_node(int key, string data, colour n_colour, node *&left, node *&right){
    node *result = new node;
    result->key = key;
    result->data = data;
    result->colour = n_colour;
    result->left = left;
    result->right = right;
    if (left  != NO_NODE)
        left->parent = result;
    if (right != NO_NODE)
        right->parent = result;
    result->parent = NO_NODE;
    return result;
}

//Look Up through Node
RBbst::node* RBbst::lookup_node(node* t, int key){
    node* n = t;
    while (n != NO_NODE){
//        int comp_result = compare(key, n->key);
        if (n->key == key){
            return n;
        }
        else if (n->key > key){
            n = n->left;
        }
        else{
            assert(n->key > key);
            n = n->right;
        }
    }
    return n;
}


// RbTree Look Up
void* RBTree::rbtree_lookup(rbtree t, void* key, compare_func compare){//verify inputs/outputs ********
    node n = lookup_node(t, key, compare);
    return n == NO_NODE ? NO_NODE : n->value;
}
// Rotate left
void RBbst::rotate_left(node *&root, node *&n){
    node* r = n->right;
    replace_node(root, n, r);
    n->right = r->left;
    if (r->left != NO_NODE){
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
}

// Rotate right
void RBbst::rotate_right(node *&root, node *&n){
    node * L = n->left;
    replace_node(root, n, L);
    n->left = L->right;
    if (L->right != NO_NODE){
        L->right->parent = n;
    }
    L->right = n;
    n->parent = L;
}


 Replaced with RBBst::insert
// Insert node into RBTree
void RBbst::rbtree_insert(rbtree t, int key, string data, compare_func compare){
}
// Inserting Case 1
void RBbst::insert_case1(node *&root, node *&n){
    if (n->parent == NO_NODE)
        n->colour = b;
    else
        insert_case2(root, n);
}

// Inserting Case 2
void RBbst::insert_case2(node *&root, node *&n){
    if (node_colour(n->parent) == b)
        return;
    else
        insert_case3(root, n);
}

// Inserting Case 3
void RBbst::insert_case3(node *&root, node *&n){
    if (node_colour(uncle(n)) == r){
        n->parent->colour = b;
        uncle(n)->colour = b;
        grandparent(n)->colour = r;
        insert_case1(root, grandparent(n));
    }
    else{
        insert_case4(root, n);
    }
}

// Inserting Case 4
void RBbst::insert_case4(node *&root, node *&n){
    if (n == n->parent->right && n->parent == grandparent(n)->left){
        rotate_left(root, n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == grandparent(n)->right){
        rotate_right(root, n->parent);
        n = n->right;
    }
    insert_case5(root, n);
}

// Inserting Case 5
void RBbst::insert_case5(node *&root, node *&n){
    n->parent->color = b;
    grandparent(n)->color = r;
    if (n == n->parent->left && n->parent == grandparent(n)->left){
        rotate_right(root, grandparent(n));
    }
    else{
        assert (n == n->parent->right && n->parent == grandparent(n)->right);
        rotate_left(root, grandparent(n));
    }
}

// Delete Node from RBTree
void RBbst::rbtree_delete(rbtree t, void* key, compare_func compare){
    node child;
    node n = lookup_node(t, key, compare);
    if (n == NO_NODE)
        return;
    if (n->left != NO_NODE && n->right != NO_NODE){
        node pred = maximum_node(n->left);
        n->key   = pred->key;
        n->value = pred->value;
        n = pred;
    }
    assert(n->left == NO_NODE || n->right == NO_NODE);
    child = n->right == NO_NODE ? n->left  : n->right;
    if (node_colour(n) == b){
        n->colour = node_colour(child);
        delete_case1(t, n);
    }
    replace_node(t, n, child);
    free(n);
    verify_properties(t);
}

// Compare two nodes
int RBbst::compare_int(void* leftp, void* rightp){ //verify input arguements
    int left = (int)leftp;
    int right = (int)rightp;
    if (left < right)
        return -1;
    else if (left > right)
        return 1;
    else{
        assert (left == right);
        return 0;
    }
}

/************************ already done *********************
// Print RBTRee
void print_tree_helper(node *&n, int indent){
}
void print_tree(rbtree t){
}
**********************************************************
*********************************************************
// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
bool RBbst::insert(int key, string data, node *&n){
  node *inserted_node = new_node(key, data, r, NO_NODE, NO_NODE);
  if (n == NO_NODE){
    n = inserted_node;
  }
  else{
    node *r = n;
    while (1){
      if (n->key < k) {
        if (r->right == NO_NODE){
          r->right = inserted_node;
          break;
        }
        else{
          r = r->right;
        }
      }
      else if (n->key > k){
        if (r->left == NO_NODE){
          r->left = inserted_node;
          break;
        }
        else{
          r = r->left;
        }
      }
      else{
        r->data = data;
        return;
      }
    }
    inserted_node->parent = n;
  }
  insert_case1(n, inserted_node);
  verify_properties(n);
}
********************************************************
// create new node with the input key and data
// attach node c to node n, returning true
bool RBbst::Attach(int key, string data, node *&n, node *&c){
  node *tmp = new node;
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
bool RBbst::AttachEqual(int key, string data, node *&n){
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
bool RBbst::leftjoin(int key, string data, node *&n) {
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
bool RBbst::rightjoin(int key, string data, node *&n) {
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
RBbst::node *RBbst::FindVictim(int key, node *&n){
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
RBbst::node *RBbst::LeftSuccessor(int key, node *&victim){
  // if there are no nodes on the right child or
  // the keys match return node
  if ((victim->right == NO_NODE) || (victim->key == key)) { return victim; }
  // otherwise look to the right for successor
  else return LeftSuccessor(key, victim->right);
}

// find the successor going down the right branch
// return pointer to successor
RBbst::node *RBbst::RightSuccessor(int key, node *&victim){
  // if there are no nodes on the left child or
  // the keys match return node
  if ((victim->left == NO_NODE) || (victim->key == key)) {return victim;}
  // otherwise look to the left for sucessor
  else return RightSuccessor(key, victim->left);
}

// transfer data and key from successor to victim
void RBbst::TDK(node *&Vic, node *&Suc){
  Vic -> key = Suc -> key;
  Vic -> data = Suc -> data;
}

// change pointer of left child parent to grandparent
// and grandparent right child to grandchild
void RNbst::RCL(node *&SP, node *&SC){
  SP->right = SC;
  SC->parent = SP;
}

// change pointer of right child parent to grandparent
// and grandparent left child to grandchild
void RBbst::RCR(node *&SP, node *&SC){
  SP->left = SC;
  SC->parent = SP;
}

// swap data and key between two nodes
void RBbst::swapElements(node* n, node* m){
   node temp;
   temp.data = n->data;
   n->data = m->data;
   m->data = temp.data;

   temp.key = n->key;
   n->key= m->key;
   m->key= temp.key;
}
*/
