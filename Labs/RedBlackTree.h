//// Author: Larry VanDenHandel
//// Purpose: Manage a red-black tree structure
//// RedBlackTree.h
 
#pragma once
 
// class prototype
template <class Comparable>
class RedBlackTree;
 
// NodeType must be a class/type that has default constructor
// and overloads < operator
template <class Comparable>
class RBTreeNode
{
 enum NodeColor {Red, Black};
 
 Comparable  value;
 RBTreeNode  *lChildPtr;
 RBTreeNode  *rChildPtr;
 NodeColor   color;
 
 //constructor
 RBTreeNode( Comparable v=Comparable(), RBTreeNode *l=NULL,
 RBTreeNode *r=NULL, NodeColor c=Black )
 : value(v), color(c), lChildPtr(l), rChildPtr(r)
 {}
 
 friend class RedBlackTree<Comparable>;
};
 
template <class Comparable>
class RedBlackTree
{
public:
 // constructor create an empty red-black tree
 RedBlackTree(void);
 
 // copy constructor for deep copy
 RedBlackTree( const RedBlackTree<Comparable>& old );
 
 // assignment operator
 const RedBlackTree<Comparable>&
 operator =( const RedBlackTree<Comparable>& rhs );
 
 // destructor to release memory space, including space for theLeaf and
 // pseudo root.
 ~RedBlackTree();
 
 // insert a value to red-black tree. This function
 // throw a bad_alloc exception if no enough space
 void insert( Comparable newItem );
 
 // print the whole tree
 void print( void ) const;
 
private:
 
 // swaps color, used in the split method
 void swapColor(RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr, RBTreeNode<Comparable>*& grandPtr);
 
 // Perform rightRotate
 // rotate the nodePtr around its left child
 // parentPtr points to the parent of nodePtr
 void rightRotate( RBTreeNode<Comparable>*& nodePtr,
 RBTreeNode<Comparable>*& parentPtr );
 
 // Perform leftRotate
 // rotate the nodePtr around its right child
 // parentPtr points to the parent of nodePtr
 void leftRotate( RBTreeNode<Comparable>*& nodePtr,
 RBTreeNode<Comparable>*& parentPtr );
 
 // split a 4-node: nodePtr
 // parentPtr points to the parent of nodePtr
 // grandPtr points to the parent of parentPtr
 // greatPtr points to the parent of grandPtr
 void split ( RBTreeNode<Comparable>* nodePtr,
 RBTreeNode<Comparable>* parentPtr,
 RBTreeNode<Comparable>* grandPtr,
 RBTreeNode<Comparable>* greatPtr );
 
 // deep copy a tree pointed by nodePtr
 RBTreeNode<Comparable> * clone( RBTreeNode<Comparable> * nodePtr ) const;
 
 // release memory of the tree, but don't release pseudo root and theLeaf
 void reclaimMemory( RBTreeNode<Comparable> *nodePtr ) const;
 
 // print the tree rooted at nodePtr
 // The parameter level specifies the level of the nodePtr in the tree.
 // You need to use this parameter to adjust indentation.
 void print( RBTreeNode<Comparable> *nodePtr, int level ) const;
 
private:
 RBTreeNode<Comparable>*     theLeaf;    // actual leaf node
 RBTreeNode<Comparable>*     m_root;     // pointer to pseudo root
};
