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

 Dependences  :

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 17  New version
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
