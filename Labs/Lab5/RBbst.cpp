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
  node* NullNode;
  enum colour { r, b };
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         enum colour colour;
  };
  *root;   */
/*
RBbst::NullNode = new node;
RBbst::NullNode->left = NO_NODE;
RBbst::NullNode->right = NO_NODE;
RBbst::NullNode->parent = NO_NODE;
RBbst::NullNode->key = 0;
RBbst::NullNode->data = "N";
*/

// Return grandparent
node* RBbst::grandparent(node *&n){
    assert (n != NullNode);
    assert (n->parent != NullNode);
    assert (n->parent->parent != NullNode);
    return n->parent->parent;
}


// Return Sibling of Node
node* RBbst::sibling(node *&n){
    assert (n != NullNode);
    assert (n->parent != NullNode);
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

 // Return Uncle of Node
node* RBbst::uncle(node *&n){
    assert (n != NullNode);
    assert (n->parent != NullNode);
    assert (n->parent->parent != NullNode);
    return sibling(n->parent);
}

// Verifying Properties of Red black Tree
void RBbst::verify_properties(rbtree t){
    verify_property_1 (t->root);
    verify_property_2 (t->root);
    verify_property_4 (t->root);	//Property 3 is not here **********
    verify_property_5 (t->root);
}

// Verifying Property 1 Each node must be red or black
void RBbst::verify_property_1(node *&n){
    assert (node_colour(n) == r || node_colour(n) == b);  //confirm node_color***********
    if (n == NullNode)
        return;
    verify_property_1(n->left);
    verify_property_1(n->right);
}

// Verifying Property 2 Root node must be black
void RBbst::verify_property_2(node *&root){
    assert (node_colour(root) == b);
}

// Where is Property 3? **********


// Verifying Property 4 If a node is red, it's children and parent must be black
void RBbst::verify_property_4(node *&n){
    if (node_colour(n) == r){
        assert (node_colour(n->left) == b);
        assert (node_colour(n->right) == b);
        assert (node_colour(n->parent) == b);
    }
    if (n == NullNode)
        return;
    verify_property_4(n->left);
    verify_property_4(n->right);
}

// Verifying Property 5 The Black height must be the same for all leaves
void RBbst::verify_property_5(node *&root){
    int black_count_path = -1;
    verify_property_5_helper(root, 0, &black_count_path);
}

void RBbst::verify_property_5_helper(node *&n, int black_count, int* path_black_count){
    if (node_colour(n) == b){
        black_count++;
    }
    if (n == NullNode){
        if (*path_black_count == -1){
            *path_black_count = black_count;
        }
        else {
            assert (black_count == *path_black_count);
        }
        return;
    }
    verify_property_5_helper(n->left,  black_count, path_black_count);
    verify_property_5_helper(n->right, black_count, path_black_count);
}

 //Returns colour of a node
 colour RBbst::node_colour(node *&n){
    return n == NullNode ? b : n->colour;
}

// Create Red Black Tree
rbtree RBbst::rbtree_create(){
    rbtree t = new rbtree_t;
    t->root = NullNode;
    verify_properties(t);
    return t;
}

/****************** verify pointers (k,v) and input arguements ***********
// Creating New Node of Reb Black Tree
node* RBbst::new_node(void* k, void* v, colour n_colour, node left, node right){
    node result = new rbtree_node;
    result->key = k;
    result->value = v;
    result->colour = n_colour;
    result->left = left;
    result->right = right;
    if (left  != NullNode)
        left->parent = result;
    if (right != NullNode)
        right->parent = result;
    result->parent = NullNode;
    return result;
}
******************************************************************/

//Look Up through Node
node* RBbst::lookup_node(rbtree t, void* key, compare_func compare){//verify inputs ********
    node* n = t->root;
    while (n != NullNode){
        int comp_result = compare(key, n->key);
        if (comp_result == 0){
            return n;
        }
        else if (comp_result < 0){
            n = n->left;
        }
        else{
            assert(comp_result > 0);
            n = n->right;
        }
    }
    return n;
}

// RbTree Look Up
void* RBTree::rbtree_lookup(rbtree t, void* key, compare_func compare){//verify inputs/outputs ********
    node n = lookup_node(t, key, compare);
    return n == NullNode ? NullNode : n->value;
}

// Rotate left
void RBbst::rotate_left(rbtree t, node *&n){
    node r = n->right;
    replace_node(t, n, r);
    n->right = r->left;
    if (r->left != NullNode){
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
}

// Rotate right
void RBbst::rotate_right(rbtree t, node *&n){
    node L = n->left;
    replace_node(t, n, L);
    n->left = L->right;
    if (L->right != NullNode){
        L->right->parent = n;
    }
    L->right = n;
    n->parent = L;
}

// Replace a node
void RBTree::replace_node(rbtree t, node oldn, node newn){
    if (oldn->parent == NullNode){
        t->root = newn;
    }
    else{
        if (oldn == oldn->parent->left)
            oldn->parent->left = newn;
        else
            oldn->parent->right = newn;
    }
    if (newn != NullNode){
        newn->parent = oldn->parent;
    }
}

// Insert node into RBTree
void RBbst::rbtree_insert(rbtree t, void* key, void* value, compare_func compare){
    node inserted_node = new_node(key, value, r, NullNode, NullNode);
    if (t->root == NullNode){
        t->root = inserted_node;
    }
    else{
        node n = t->root;
        while (1){
            int comp_result = compare(key, n->key);
            if (comp_result == 0) {
                n->value = value;
                return;
            }
            else if (comp_result < 0){
                if (n->left == NullNode){
                    n->left = inserted_node;
                    break;
                }
                else{
                    n = n->left;
                }
            }
            else{
                assert (comp_result > 0);
                if (n->right == NullNode){
                    n->right = inserted_node;
                    break;
                }
                else{
                    n = n->right;
                }
            }
        }
        inserted_node->parent = n;
    }
    insert_case1(t, inserted_node);
    verify_properties(t);
}

// Inserting Case 1
void RBbst::insert_case1(rbtree t, node *&n){
    if (n->parent == NullNode)
        n->colour = b;
    else
        insert_case2(t, n);
}

// Inserting Case 2
void RBbst::insert_case2(rbtree t, node *&n){
    if (node_colour(n->parent) == b)
        return;
    else
        insert_case3(t, n);
}

// Inserting Case 3
void RBbst::insert_case3(rbtree t, node *&n){
    if (node_colour(uncle(n)) == r){
        n->parent->colour = b;
        uncle(n)->colour = b;
        grandparent(n)->colour = r;
        insert_case1(t, grandparent(n));
    }
    else{
        insert_case4(t, n);
    }
}

// Inserting Case 4
void RBbst::insert_case4(rbtree t, node *&n){
    if (n == n->parent->right && n->parent == grandparent(n)->left){
        rotate_left(t, n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == grandparent(n)->right){
        rotate_right(t, n->parent);
        n = n->right;
    }
    insert_case5(t, n);
}

// Inserting Case 5
void RBbst::insert_case5(rbtree t, node *&n){
    n->parent->color = b;
    grandparent(n)->color = r;
    if (n == n->parent->left && n->parent == grandparent(n)->left){
        rotate_right(t, grandparent(n));
    }
    else{
        assert (n == n->parent->right && n->parent == grandparent(n)->right);
        rotate_left(t, grandparent(n));
    }
}

// Delete Node from RBTree
void RBbst::rbtree_delete(rbtree t, void* key, compare_func compare){
    node child;
    node n = lookup_node(t, key, compare);
    if (n == NullNode)
        return;
    if (n->left != NullNode && n->right != NullNode){
        node pred = maximum_node(n->left);
        n->key   = pred->key;
        n->value = pred->value;
        n = pred;
    }
    assert(n->left == NullNode || n->right == NullNode);
    child = n->right == NullNode ? n->left  : n->right;
    if (node_colour(n) == b){
        n->colour = node_colour(child);
        delete_case1(t, n);
    }
    replace_node(t, n, child);
    free(n);
    verify_properties(t);
}

// Returns Maximum node
node* RBbst::maximum_node(node *&n){
    assert (n != NullNode);
    while (n->right != NullNode){
        n = n->right;
    }
    return n;
}

// Deleting Case 1
void RBbst::delete_case1(rbtree t, node *&n){
    if (n->parent == NullNode)
        return;
    else
        delete_case2(t, n);
}

// Deleting Case 2
void RBbst::delete_case2(rbtree t, node *&n){
    if (node_colour(sibling(n)) == r)    {
        n->parent->coluor = r;
        sibling(n)->colour = b;
        if (n == n->parent->left)
            rotate_left(t, n->parent);
        else
            rotate_right(t, n->parent);
   }
    delete_case3(t, n);
}

// Deleting Case 3
void RBbst::delete_case3(rbtree t, node *&n){
    if (node_colour(n->parent) == b && node_colour(sibling(n)) == b &&
        node_colour(sibling(n)->left) == b && node_colour(sibling(n)->right) == b){
        sibling(n)->color = r;
        delete_case1(t, n->parent);
    }
    else
        delete_case4(t, n);
}

// Deleting Case 4
void RBbst::delete_case4(rbtree t, node *&n){
    if (node_colour(n->parent) == r && node_colour(sibling(n)) == b &&
        node_colour(sibling(n)->left) == b && node_colour(sibling(n)->right) == b){
        sibling(n)->color = r;
        n->parent->color = b;
    }
    else
        delete_case5(t, n);
}

// Deleting Case 5
void RBbst::delete_case5(rbtree t, node *&n){
    if (n == n->parent->left && node_colour(sibling(n)) == b &&
        node_colour(sibling(n)->left) == r && node_colour(sibling(n)->right) == b){
        sibling(n)->colour = r;
        sibling(n)->left->colour = b;
        rotate_right(t, sibling(n));
    }
    else if (n == n->parent->right && node_colour(sibling(n)) == b &&
             node_colour(sibling(n)->right) == r && node_colour(sibling(n)->left) == b){
        sibling(n)->colour = r;
        sibling(n)->right->colour = b;
        rotate_left(t, sibling(n));
    }
    delete_case6(t, n);
}

// Deleting Case 6
void RBbst::delete_case6(rbtree t, node *&n){
    sibling(n)->colour = node_colour(n->parent);
    n->parent->colour = b;
    if (n == n->parent->left){
        assert (node_colour(sibling(n)->right) == r);
        sibling(n)->right->colour = b;
        rotate_left(t, n->parent);
    }
    else{
        assert (node_colour(sibling(n)->left) == r);
        sibling(n)->left->colour = b;
        rotate_right(t, n->parent);
    }
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
    int i;
    if (n == NULL){
        fputs("<empty tree>", stdout);
        return;
    }
    if (n->right != NULL){
        print_tree_helper(n->right, indent + INDENT_STEP);
    }
    for(i = 0; i < indent; i++)
        fputs(" ", stdout);
    if (n->color == BLACK)
        cout<<(int)n->key<<endl;
    else
        cout<<"<"<<(int)n->key<<">"<<endl;
    if (n->left != NULL){
        print_tree_helper(n->left, indent + INDENT_STEP);
    }
}

void print_tree(rbtree t){
    print_tree_helper(t->root, 0);
    puts("");
}
***********************************************************/

// insert a new node in the bst rooted at n,
// returning true if successful, false otherwise
bool bst::insert(int k, string d, node* &n){
  // insert the node at the appropiate location
  // if root is null, create a new node with information and return true
  if (n == NO_NODE) {
   	n = new node;
	n->left = NO_NODE;
	n->right = NO_NODE;
        n->parent = NO_NODE; //new NullNode;
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
/*2:c (5 b N N)
5:a (N b 2 7)
7:b (5 b N N)	*/
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

//Change to printout as specified in Lab5 Preorder Print
void bst::PreOrdprint(node *n){
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
