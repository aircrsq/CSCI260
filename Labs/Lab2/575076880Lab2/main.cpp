/************************************************************************
 Design Unit  : Lab2

 File Name    : main.cpp

 Purpose      : Solve a Tromino problem

 Note         : Prompts user for
                Size of screen
                Size of board and
                location of hole

 Limitations  :

 Errors       : none known

 Modules      :

 Dependences  : gameboard.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 17  New version
 1.1	      DB      Sep 19  Code changed to incorporate functions
*************************************************************************/

#include "gameboard.h"

using namespace std;

int main(){

  gameboard * myboard = new gameboard();

  //Get blank square
  myboard->GetBlankSquare();

  //Solve board
  myboard->SolveBoard(0, 0, myboard->boardside, myboard->i-1, myboard->j-1);

  //Display board
  myboard->PrintBoard();

  return 0;
}
