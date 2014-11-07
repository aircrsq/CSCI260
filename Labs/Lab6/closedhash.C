/*****************************************************************/
/**        closedhash.C                                          */
/**        written by D.Wessels (as hash.C)                      */
/**        modified by G. Pruesse (to use closed hashing)        */
/**        Oct 16, 2007                                          */
/**        modified Oct 27, 2014 -- added header file          */
/*****************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <list>
#include <stdlib.h>
//include for file handling
#include <fstream>

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

// define a hash table of record pointers,
//    with methods to insert a new record into the table
//    and lookup a record based on its key
class hashtable {
   private:
      record* *table;
      int tsize;
      int hash(keytype k, int i);
      int classhash(keytype k, int i);
      int myhash(keytype k, int i);
      int collisions;
      int longestsearch;
      int entries;
   public:
      hashtable(int sz = 0);
      ~hashtable();
      bool insert(record *r);
      bool classinsert(record *r);
      bool myinsert(record *r);
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
       //bit shifting
       hash = (hash << 6) ^ (hash <<  3) ^ k[i];
   }
   if (hash < 0) hash = -hash;
   return ((hash + offset)  % tsize  );
}

int hashtable::classhash(keytype k,int offset)
{
   int length = k.length();
   int hash = length;
   int AsciiTotal = 0;
   for(std::string::size_type i = 0; i < k.size(); ++i) {
     AsciiTotal += k[i];
   }
   for (int i = 0; i < length; i++) {
       if (DEBUG) {
          int h1 = hash << 12;
          int h2 = hash << 6;
          int h3 = k[i];
          cout << h1 << "^" << h2 << "^" << h3 << "=" << hash << endl;
       }
       //bit shifting
       hash = (hash << 12) ^ (hash <<  6) ^ k[i];
   }
   hash = AsciiTotal % tsize;
   if (hash < 0) hash = -hash;
   return ((hash + offset)  % tsize  );
}
int hashtable::myhash(keytype k,int offset)
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
       //bit shifting
       hash = (hash << 6) ^ (hash <<  3) ^ k[i];
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
   //variable for containing the number of entries that are not null
   int Entries = 0;
   if (table) {
      for (int i = 0; i < tsize; i++) {
        if ((table[i]) != NULL){Entries++;}
        if (table[i]) delete table[i];
      }
      delete table;
   }
   cout << "Total collisions: " << collisions;
   cout << " out of " << Entries << " entries";
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

// insert calls the hash function to find where to insert the
//    record, and pushes the record into the back of that list
bool hashtable::classinsert(record *r)
{
   if (!r) return false;
   if (!table) return false;
   int i;
   int pos = classhash(r->key,i=0);
   while (table[pos]!=NULL && i<tsize)
	pos = classhash(r->key, ++i);
   if ((pos < 0) || (pos >= tsize)) {
      cout << "Hash generated position " << pos << " on " << r->key << endl;
      return false;
   }
   table[pos]=r;
   cout << "inserting " << setw(2) << r->key << ":";
   cout << " in hash row " << pos << " on "<< i<<"th try. "<< endl;
   if (i>longestsearch) longestsearch = i;
   collisions += i;
   return true;
}

// insert calls the hash function to find where to insert the
//    record, and pushes the record into the back of that list
bool hashtable::myinsert(record *r)
{
   if (!r) return false;
   if (!table) return false;

   int i;
   int pos = myhash(r->key,i=0);
   while (table[pos]!=NULL && i<tsize)
	pos = myhash(r->key, ++i);
   if ((pos < 0) || (pos >= tsize)) {
      cout << "Hash generated position " << pos << " on " << r->key << endl;
      return false;
   }
   table[pos]=r;
   cout << "inserting " << setw(2) << r->key << ":";
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
int main(){
   char data[13];
   int size = 0;
   int numtests = 0;
   string entry;
   char UserOption = 'A';
   string line;
   string InputFileName;
  while (UserOption != 'Q'){
    cout << "How would you like to input data?" << endl;
    cout << "Q - Quit?" << endl;
    cout << "F - Read from a file?" << endl;
    cout << "R - Random generated?" << endl;
    cout << "C - Class hash" << endl;
    cout << "M - My Hash?" << endl;
    cin >> UserOption;
    UserOption = toupper(UserOption);
    switch (UserOption) {
     case 'F': {//Reads the file MRK for input
               ifstream myfile ("MRK");
               // allow the user to select the size of the table
               cout << "How large a table would you like to work with?" << endl;
               cout << "(e.g. a prime number about the size of ";
               cout << "your planned number of data entries)" << endl;
               cin >> size;
               // allow the user to select the number of test records
               cout << "How many test values would you like to insert?" << endl;
               do {
                 cin >> entry;
                 if (atoi(entry.c_str()) < 1) {
                   cout << entry << " is not a positive integer value, ";
                   cout << endl << "please try again" << endl;
                 } else numtests = atoi(entry.c_str());
               } while (numtests < 0 || numtests > size);
               // allocate the hash table, quit if it fails
               hashtable *H = new hashtable(size);
               if (H == NULL) {
                 cout << "unable to allocate sufficient table space, sorry!" << endl;
                 return 1;
               }
               // allocate space for the test records, quit if it fails
               keytype *keyvals = new keytype[size];
               if (keyvals == NULL) {
                 cout << "unable to allocate sufficient test data, sorry!" << endl;
                 delete H;
                 return 2;
               }
               int InputLines = 0;
               if (myfile.is_open()){
                 while ((getline (myfile,line)) && (InputLines < numtests)){
                   cout << line << '\n';
                   keyvals[InputLines] = line;
                   record *r = new record;
                   if (!r) continue;
                   r->key = keyvals[InputLines];
                   H->insert(r);
                   InputLines++;
                 }
                 myfile.close();
                 // go through the list of remembered keys and try to
                 //    retrieve each of them from the hash table
                 cout << endl << "Looking for the records we created" << endl;
                 for (int j = 0; j < numtests; j++) {
                   record *s = H->lookup(keyvals[j]);
                   cout << keyvals[j];
                   if (!s) cout << "Could not find record " << keyvals[j] << endl;
                   else {
                     cout << setw(2) << s->key;// << ":" << s->data;
                     cout << " found successfully" << endl;
                   }
                 }
                 // deallocate the hash table and the storage
                 //    for remembered keys
                 delete H;
                 //delete keyvals;
               }
               else cout << "Unable to open file";
       break;}
     case 'C': {//Reads the file MRK for input
               ifstream myfile ("MRK");
               // allow the user to select the size of the table
               cout << "How large a table would you like to work with?" << endl;
               cout << "(e.g. a prime number about the size of ";
               cout << "your planned number of data entries)" << endl;
               cin >> size;
               // allow the user to select the number of test records
               cout << "How many test values would you like to insert?" << endl;
               do {
                 cin >> entry;
                 if (atoi(entry.c_str()) < 1) {
                   cout << entry << " is not a positive integer value, ";
                   cout << endl << "please try again" << endl;
                 } else numtests = atoi(entry.c_str());
               } while (numtests < 0 || numtests > size);
               // allocate the hash table, quit if it fails
               hashtable *H = new hashtable(size);
               if (H == NULL) {
                 cout << "unable to allocate sufficient table space, sorry!" << endl;
                 return 1;
               }
               // allocate space for the test records, quit if it fails
               keytype *keyvals = new keytype[size];
               if (keyvals == NULL) {
                 cout << "unable to allocate sufficient test data, sorry!" << endl;
                 delete H;
                 return 2;
               }
               int InputLines = 0;
               if (myfile.is_open()){
                 while ((getline (myfile,line)) && (InputLines < numtests)){
                   keyvals[InputLines] = line;
                   record *r = new record;
                   if (!r) continue;
                   r->key = keyvals[InputLines];
                   H->classinsert(r);
                   InputLines++;
                 }
                 myfile.close();
                 // go through the list of remembered keys and try to
                 //    retrieve each of them from the hash table
                 cout << endl << "Looking for the records we created" << endl;
                 for (int j = 0; j < numtests; j++) {
                   record *s = H->lookup(keyvals[j]);
                   if (!s) cout << "Could not find record " << keyvals[j] << endl;
                   else {
                     cout << setw(2) << s->key;// << ":" << s->data;
                     cout << " found successfully" << endl;
                   }
                 }
                 // deallocate the hash table and the storage
                 //    for remembered keys
                 delete H;
                 //delete keyvals;
               }
               else cout << "Unable to open file";
       break;}
     case 'M': {//Reads the file MRK for input
               ifstream myfile ("MRK");
               // allow the user to select the size of the table
               cout << "How large a table would you like to work with?" << endl;
               cout << "(e.g. a prime number about the size of ";
               cout << "your planned number of data entries)" << endl;
               cin >> size;
               // allow the user to select the number of test records
               cout << "How many test values would you like to insert?" << endl;
               do {
                 cin >> entry;
                 if (atoi(entry.c_str()) < 1) {
                   cout << entry << " is not a positive integer value, ";
                   cout << endl << "please try again" << endl;
                 } else numtests = atoi(entry.c_str());
               } while (numtests < 0 || numtests > size);
               // allocate the hash table, quit if it fails
               hashtable *H = new hashtable(size);
               if (H == NULL) {
                 cout << "unable to allocate sufficient table space, sorry!" << endl;
                 return 1;
               }
               // allocate space for the test records, quit if it fails
               keytype *keyvals = new keytype[size];
               if (keyvals == NULL) {
                 cout << "unable to allocate sufficient test data, sorry!" << endl;
                 delete H;
                 return 2;
               }
               int InputLines = 0;
               if (myfile.is_open()){
                 while ((getline (myfile,line)) && (InputLines < numtests)){
                   cout << line << '\n';
                   keyvals[InputLines] = line;
                   record *r = new record;
                   if (!r) continue;
                   r->key = keyvals[InputLines];
                   H->myinsert(r);
                   InputLines++;
                 }
                 myfile.close();
                 // go through the list of remembered keys and try to
                 //    retrieve each of them from the hash table
                 cout << endl << "Looking for the records we created" << endl;
                 for (int j = 0; j < numtests; j++) {
                   record *s = H->lookup(keyvals[j]);
                   if (!s) cout << "Could not find record " << keyvals[j] << endl;
                   else {
                     cout << setw(2) << s->key;// << ":" << s->data;
                     cout << " found successfully" << endl;
                   }
                 }
                 // deallocate the hash table and the storage
                 //    for remembered keys
                 delete H;
                 //delete keyvals;
               }
               else cout << "Unable to open file";
       break;}
     case 'R': {//call the manual insert function
               // allow the user to select the size of the table
               cout << "How large a table would you like to work with?" << endl;
               cout << "(e.g. a prime number about the size of ";
               cout << "your planned number of data entries)" << endl;
               do {
                 cin >> entry;
                 if (atoi(entry.c_str()) < 1) {
                   cout << entry << " is not a positive integer value, ";
                   cout << endl << "please try again" << endl;
                 } else size = atoi(entry.c_str());
               } while (size < 1);
               // allow the user to select the number of test records
               cout << "How many test values would you like to insert?" << endl;
               do {
                 cin >> entry;
                 if (atoi(entry.c_str()) < 1) {
                   cout << entry << " is not a positive integer value, ";
                   cout << endl << "please try again" << endl;
                 } else numtests = atoi(entry.c_str());
               } while (numtests < 0 || numtests > size);
               // allocate the hash table, quit if it fails
               hashtable *H = new hashtable(size);
               if (H == NULL) {
                 cout << "unable to allocate sufficient table space, sorry!" << endl;
                 return 1;
               }
               // allocate space for the test records, quit if it fails
               keytype *keyvals = new keytype[size];
               if (keyvals == NULL) {
                 cout << "unable to allocate sufficient test data, sorry!" << endl;
                 delete H;
                 return 2;
               }
               // create the desired number of test records,
               //    each with a random key,
               // remember their key values in the keyvals array,
               //    and insert them in the hash table
               cout << "Creating records with random keys and inserting in hash table" << endl;
               for (int i = 0; i < numtests; i++) {
                 keyvals[i] = H->nextkey();
                 record *r = new record;
                 if (!r) continue;
                 r->key = keyvals[i];
                 r->data = i;
                 H->insert(r);
               }
               // go through the list of remembered keys and try to
               //    retrieve each of them from the hash table
               cout << endl << "Looking for the records we created" << endl;
               for (int j = 0; j < numtests; j++) {
                 record *s = H->lookup(keyvals[j]);
                 if (!s) cout << "Could not find record " << keyvals[j] << endl;
                 else {
                   cout << setw(2) << s->key << ":" << s->data;
                   cout << " found successfully" << endl;
                 }
               }
               // deallocate the hash table and the storage
               //    for remembered keys
               delete H;
               //delete keyvals;
       break;}
     case 'Q':{ //Call the remove funtion
               cout << "quit." << endl;
       break;}
    default:  cout << "You have entered an invalid command" << endl;
    }
  }
}


