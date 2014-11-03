/*****************************************************************/
/**        closedhash.C                                          */
/**        written by D.Wessels (as hash.C)                      */
/**        modified by G. Pruesse (to use closed hashing)        */
/**        Oct 16, 2007                                          */
/**        modified Oct 27, 2014 -- added header file          */
/*****************************************************************/
/************************************************************************
 Design Unit  : Lab6

 File Name    : closedhash.cpp

 Purpose      :

 Note         :

 Limitations  :

 Errors       : none known

 Modules      : closedhash.h

 Dependences  : closedhash.h
              : iostream
              : iomanip
              : string
              : ctime
              : list
              : stdlib.h

 Author       : David Burneau, 575076880 Vancouver Island University
              : Modified from the original source file as stated above.

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 2.0          DB      Oct 27  Modified original source
*************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <list>
#include <stdlib.h>
using namespace std;

// print some extra info while in debugging mode
const bool DEBUG = false;

// can change keytype and datatype to anything
//     as long as the generators and hash functions
//     are updated appropriately
typedef string keytype;
typedef float datatype;

// define what the contents of a record look like
struct record {
   keytype key;
   datatype data;
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
int closedhash::hash(keytype k,int offset)
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
keytype closedhash::nextkey()
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
closedhash::hashtable(int sz)
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
closedhash::~hashtable()
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
bool closedhash::insert(record *r)
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
record *closedhash::lookup(keytype k)
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
