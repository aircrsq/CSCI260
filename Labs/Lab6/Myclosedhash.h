#ifndef CLOSEDHASH
#define CLOSEDHASH
/************************************************************************
 Design Unit  : Lab6

 File Name    : closedhash.h

 Purpose      : Header file for closedhash

 Note         :

 Limitations  : none known

 Errors       : none known

 Modules      :

 Dependences  : none

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 27  New version Original code provide by
                              Professor Gara Pruesse
*************************************************************************/
#include<string>
#include<iostream>

using namespace std;

// print some extra info while in debugging mode
const bool DEBUG = false;

// can change keytype and datatype to anything
//     as long as the generators and hash functions
//     are updated appropriately
typedef string keytype;
typedef float datatype;


// define a hash table of record pointers,
//    with methods to insert a new record into the table
//    and lookup a record based on its key
class hashtable {

   private:
   // define what the contents of a record look like
   struct record {
   keytype key;
   datatype data;
};

      int hash(keytype k,int offset);
      keytype nextkey();
      bool insert(record *r);
      record *lookup(keytype k);

      record* *table;
      int tsize;
      int hash(keytype k, int i);
      int collisions;
      int longestsearch;
      int entries;
   public:
      hashtable(int sz = 0);
      ~hashtable();
      bool insert(record *r);
      record *lookup(keytype k);
      keytype nextkey();
};

// ------------- methods dependent on the key type --------------

// the hash function relies on knowledge of the keytype,
//     here assumed to be a string
//
// we're using a rotating hash function,
// where, on processing each character, we:
//    make a copy of the current hash value
//         and shift it 12 bits
//    make another copy of the hash value
//         and shift it 6 bits
//    take the exclusive-or of the two shifted
//         values and the next key character
int hashtable::hash(keytype k,int offset)
{
   int length = k.length();
   int hash = length;
   for (int i = 0; i < length; i++) {
       if (DEBUG) {
          int h1 = hash << 12;
          int h2 = hash << 6;
          int h3 = k[i];
          cout << h1 << "^" << h2 << "^" << h3 << "=" << hash << endl;
       }
       hash = (hash << 12) ^ (hash <<  6) ^ k[i];
   }
   if (hash < 0) hash = -hash;
   return ((hash + offset)  % tsize  );
}

// generate random key
keytype hashtable::nextkey()
{
   keytype k;
   // here we rely on the actual datatype of the key,
   //      currently known to be a string,
   // we'll generate a random string of length 4..12
   int length = 4 + (random() % 8);
   for (int i = 0; i < length; i++) {
       char c = (random() % 26) + 'a';
       k += c;
   }
   return k;
}

// ------------- methods independent of the key type ------------

// the constructor allocates a table with sz lists of records,
//     and remembers the size of the table
hashtable::hashtable(int sz)
{
   if (sz < 0) sz = 0;
   table = new record*[sz];
   if (!table) tsize = 0;
   else tsize = sz;
   // initialize the random number generator
   srandom((unsigned int)(time(NULL)));
   collisions = 0;
   longestsearch = 0;

}

// the destructor deallocates each record in each list
//     in the table
// and also computes the number of collisions in the
//     hash table and the length of the largest chain
hashtable::~hashtable()
{
   if (table) {
      for (int i = 0; i < tsize; i++) {
             if (table[i]) delete table[i];
      }
      delete table;
   }
   cout << "Total collisions: " << collisions;
   cout << " out of " << entries << " entries";
   cout << ", largest chain: " << longestsearch << endl;
}

// insert calls the hash function to find where to insert the
//    record, and pushes the record into the back of that list
bool hashtable::insert(record *r)
{
   if (!r) return false;
   if (!table) return false;

   int i;
   int pos = hash(r->key,i=0);
   while (table[pos]!=NULL && i<tsize)
	pos = hash(r->key, ++i);
   if ((pos < 0) || (pos >= tsize)) {
      cout << "Hash generated position " << pos << " on " << r->key << endl;
      return false;
   }
   table[pos]=r;
   cout << "inserting " << setw(2) << r->key << ":" << r->data;
   cout << " in hash row " << pos << " on "<< i<<"th try. "<< endl;
   if (i>longestsearch) longestsearch = i;
   collisions += i;
   return true;
}

// lookup calls the hash function to find which list should
//    contain the record with the specified key,
//    then searches that list and returns the record found
// (or null if no matching record is found)
record *hashtable::lookup(keytype k)
{
   if (!table) return NULL;
   int i;
   int pos = hash(k,i=0);
   if ((pos < 0) || (pos >= tsize)) return NULL;
   while (table[pos]->key != k && ++i<tsize) {
	pos = hash(k, i);
   }
   if (table[pos]->key == k) return table[pos];

   return NULL;
}

// the main routine generates a bunch of records with
//     random key values, makes note of what key values they had,
//     and inserts them in the hash table
// it then goes through its list of key values and tests the
//     hash table to see if it can find them


class RBbst{
  private:
  struct node {
         node *right, *left, *parent;
         string data;
         int key;
         int colour;
  };
  // we maintain a pointer to the root of the tree
  node * root;
  node * Sentinel;

  // private, recursive routines (used by the public methods)
  // see RBbst.cpp file for explanation
  void insertNode(int, string, node *&);
  node * Find(node *&,int ,int );
  void insert_case1(node *&, node *&);
  void insert_case2(node *&, node *&);
  void insert_case3(node *&, node *&);
  void insert_case4(node *&, node *&);
  void insert_case5(node *&, node *&);
  node * uncle(node *&);
  node * grandparent(node *&);
  node * sibling(node *&);
  void rotate_left(node *, node *);
  void rotate_right(node *, node *);
  string search(int, node *&);
  void print(node *&);
  void debugprint(node *&);
  void PreOrdprint(node *&);
  bool deleteElement(int, node*&);
  node * maximum_node(node *&);
  void delete_case1(node *&, node *&);
  void delete_case2(node *&, node *&);
  void delete_case3(node *&, node *&);
  void delete_case4(node *&, node *&);
  void delete_case5(node *&, node *&);
  void delete_case6(node *&, node *&);
  int node_colour(node *);
  void deallocate(node *&);
  void swapElements(node*& , node*&);

  public:
  //Constructor
  RBbst() {
    //Make a new node initialized as a sentinel
    //and have it assigned to root
    Sentinel = new node;
    Sentinel->parent = Sentinel;
    Sentinel->left = Sentinel;
    Sentinel->right = Sentinel;
    Sentinel->key = -99999999;
    Sentinel->data = "Sentinel";
    Sentinel->colour = BLACK;
    root = Sentinel;
  }
  //Destructor
  ~RBbst() { deallocate(root); }

  //prints tree in Inorder
  void display() {
    cout << endl;
    print(root);
  }

  //prints node key and pointer information
  void debug(){
    cout << endl;
    debugprint(root);
  }

  //prints node key and pointer information
  void PreOrd(){
    PreOrdprint(root);
  }

  //finds node k and returns the data associated with node
  void find(int k) {
    string SearchResult = search(k,root);
    cout << SearchResult;
  }

  //Inserts a node with key k and data d into the tree
  bool insert(int key, string data) {
    insertNode(key, data, root);
    return true;
  }

  //removes a node and its information from the tree
  bool deleteElement(int k) {
    if (deleteElement(k, root))
      return true;
    else return false;
  }
};
#endif

