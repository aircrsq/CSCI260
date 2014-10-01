#include "bst.h"
#include <iostream>

using namespace std;

char getcommand();
void printmenu();
bool processcommand(char cmd, bst &tree);

int main()
{
   bst B;
   
   printmenu();
   char cmd = getcommand();
   while (processcommand(cmd, B)) { 
      cout << endl;
      cmd = getcommand();
   }

   return 0;
}

char getcommand()
{
   cout << "Enter your command choice (I, R, P, D, H, Q, or F)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'F':
      case 'H':
      case 'I':
      case 'R':
      case 'M':
      case 'P':
      case 'Q':
      case 'D': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu()
{
   cout << "Enter I to insert a new element," << endl;
   cout << "   or R to remove an element with given key," << endl;
   cout << "   or P to print all elements," << endl;
   cout << "   or D to for debug data display," << endl;
   cout << "   or H for help," << endl;
   cout << "   or Q to quit," << endl;
   cout << "   or F to find a node." << endl;
}

bool processcommand(char cmd, bst &tree)
{
   int k; string d;
   switch (cmd) {
      case 'F': cout << "Enter the key integer you wish to find." << endl;
                cin >> k;
                tree.find(k);
      case 'H': printmenu(); 
                break;
      case 'I': cout << "Enter the key integer" << endl;
                cin >> k;
                cout << "Enter the data word" << endl;
                cin >> d;
                cout << "(" << k << "," << d << ") ";
                if (tree.insert(k, d)) 
                   cout << "was inserted successfully" << endl;
                else cout << "was not inserted correctly" << endl;
                break;
      case 'R': cout << "Enter the key integer" << endl;
      	        cin >> k;
		if (tree.deleteElement(k))
		    cout << k << " was successfully deleted." << endl;
		else cout << k << " was not deleted -- not in tree." << endl;
                break;
      case 'P': cout << "The tree contents are: ";
                tree.display();
                break; 
      case 'D': cout << "The tree debug data is:" << endl;
                tree.debug();
                break; 
      default:  return false;
   }
   return true;
}

