/************************************************************************
 Design Unit  : Lab1

 File Name    : Testapp.cpp

 Purpose      : Test application for unionfind

 Note         : Prompts user for input data filename

 Limitations  : Input data file must be
                   First line - number of elemanets in the array
                   Remaining lines
                      - a small "u" or "f" indicating union or find respectively,
                      followed by a space
                      - an integer within the limits of the array followed
                      by a space
                      - an second integer within the limits of the array,
                      followed by a newline

 Errors       : none known

 Modules      : unionfind.h

 Dependences  : unionfind.h
              : Test input data file
              : iostream
              : fstream
              : string
              : sstream
              : stdlib.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 08  New version
*************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>


using namespace std;

/* string GetFileName(){

}	*/

int main()
{
  char *** board;
	board[0][0] = "\u2586";
	board[1][0] = "\u2589";
	board[1][1] = "\u258B";
  for (int i = 0; i <= 1; i++){
    for (int j = 0; j <= 1; j++){
      cout << board[i][j];
    }
  }
}
