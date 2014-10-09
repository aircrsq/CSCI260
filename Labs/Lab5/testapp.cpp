/************************************************************************
 Design Unit  : Lab5

 File Name    : testapp.cpp

 Purpose      : creates a test application for the bst data type

 Note         : Prompts user for
                inputs for nodes
                removal of nodes
                finding of nodes
                printing of the tree in Inorder
                Help menu, and
                quit

 Limitations  : unknown

 Errors       : none known

 Modules      :

 Dependences  : bst.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 06  New version some code was implemented from original
                              version provided by Professor Gara Pruesse
*************************************************************************/
#include "RBbst.h"
#include <iostream>

using namespace std;

char getcommand();
void printmenu();
bool processcommand(char cmd, RBbst &tree);

int main()
{
   RBbst B;

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
   cout << "Enter your command choice (A, D, P, H, I, Q, R, F, or S)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'A':
      case 'F':
      case 'H':
      case 'I':
      case 'R':
      case 'P':
      case 'Q':
      case 'D': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu()
{
   cout << "Enter A to print in pre-order," << endl;
   cout << "   or I to insert a new element," << endl;
   cout << "   or R to remove an element with given key," << endl;
   cout << "   or P to print all elements," << endl;
   cout << "   or D to for debug data display," << endl;
   cout << "   or H for help," << endl;
   cout << "   or Q to quit," << endl;
   cout << "   or F to find a node." << endl;
}

bool processcommand(char cmd, RBbst &tree)
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
/*      case 'P': cout << "The tree contents are: ";
                tree.display();
                break;  */
      case 'D': cout << "The tree debug data is:" << endl;
                tree.debug();
                break;
 /*     case 'A': cout << "The tree contents in Preorder is:" << endl;
                tree.PreOrd();  */
      default:  return false;
   }
   return true;
}

