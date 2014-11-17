/************************************************************************
 Design Unit  : Lab6

 File Name    : testapp.cpp

 Purpose      : creates a test application for the bst data type

 Note         :

 Limitations  : unknown

 Errors       : none known

 Modules      :

 Dependences  : bst.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 27  Modified for closedhash testing Lab6
*************************************************************************/
#include "closedhash.h"
#include <iostream>

using namespace std;

char getcommand();
void printmenu();
bool processcommand(char cmd, closedhast &H);

int main(){
   int size = 0;
   int numtests = 0;
   string entry;

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
   delete keyvals;




//   RBbst B;
     closedhash H;
   printmenu();
   char cmd = getcommand();
   while (processcommand(cmd, H)) {
      cout << endl;
      cmd = getcommand();
   }
   return 0;
}

char getcommand(){
   cout << "Enter your command choice (A, F, H, M, R, or Q)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'A':
      case 'M':
      case 'H':
      case 'F':
      case 'R':
//      case 'P':
//      case 'Q':
      case 'Q': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu(){
   cout << "Enter A reading from file," << endl;
   cout << "   or M for manual random insert." << endl;
   cout << "   or R to remove an element with given key," << endl;
   cout << "   or F to find a key." << endl;
   cout << "   or H for help," << endl;
   cout << "   or Q to quit," << endl;
//   cout << "   or P to print all elements," << endl;
//   cout << "   or D to for debug data display," << endl;
}

bool processcommand(char cmd, RBbst &tree){
   string k; //string d;
   switch (cmd) {
      case 'A': cout << "Enter the name of the input file." << endl;
                //call the read file function
                //tree.PreOrd();
                break;
      case 'M': //call the manual insert function
                break;
      case 'R': //Call the remove funtion
/*      case 'R': cout << "Enter the key" << endl;
      	        cin >> k;
		if (tree.deleteElement(k))
		    cout << k << " was successfully deleted." << endl;
		else cout << k << " was not deleted -- not in tree." << endl;
                break;  */
      case 'F': cout << "Enter the key you wish to find." << endl;
                cin >> k;
                //call the find function
                //tree.find(k);
                break;
      case 'H': printmenu();
                break;
/*      case 'I': cout << "Enter the key integer" << endl;
                cin >> k;
                cout << "Enter the data word" << endl;
                cin >> d;
                cout << "(" << k << "," << d << ") ";
                if (tree.insert(k, d))
                   cout << "was inserted successfully" << endl;
                else cout << "was not inserted correctly" << endl;
                break;  */

/*      case 'P': cout << "The tree contents are: ";
                tree.display();
                break;  */
/*      case 'D': cout << "The tree debug data is:" << endl;
                tree.debug();
                break;  */
      default:  return false;
   }
   return true;
}


