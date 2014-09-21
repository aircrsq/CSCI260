/************************************************************************
 Design Unit  : Lab2

 File Name    : gameboard.cpp

 Purpose      :

 Note         :

 Limitations  :

 Errors       : none known

 Modules      : gameboard.h

 Dependences  : iostream
	      : fstream
	      : string
	      : sstream
	      : stdlib.h
	      : gameboard.h
	      : math.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 16  New version
 1.1	      DB      Sep 19  Code for recursion added
*************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "gameboard.h"
#include "math.h"

using namespace std;

//Constructor
gameboard::gameboard(){
  cout << "Enter the width of your screen, for printing (in characters):";
  cin >> n;
  double param, result;
  param = n;
  result = log2 (param);
  cout << "Enter the power k, making a chessboard 2^k x 2^k less than " << result <<";";
  cin >> k;
  boardside =(int)pow((double)2,(double)k);
  board = new char ** [boardside];
  for (int r=0; r < boardside; r++){
    board[r] = new char * [boardside];
  }
}

//Get Blank Square
void gameboard::GetBlankSquare(){
  char * BlankSquare = "\u2592";
  cout << "Enter the row and column of the missing square, < " << boardside 
	<< " separated by a space:";
  cin >> i >> j;
  board[i-1][j-1] = BlankSquare;
  cout << "Cell " << i << " " << j << " is the blank square. \n";
}

//Solve Board
void gameboard::SolveBoard(int x1, int y1, int side, int BlankX, int BlankY){
  char * Fill = "\u2588";
  char * RightFill = "\u25C0";
  char * LeftFill = "\u25B6";
  char * BottomFill = "\u25B2";
  char * TopFill = "\u25BC";
  char * BlankSquare = "\u2592";

  int halfside = side/2;
  if (halfside - 1 == 0){
    //TroOne
    if((BlankX <= x1 + halfside -1) && (BlankY <= y1 + halfside -1)){
      TroOne(x1, y1, halfside);
    }
    //TroTwo
    else if ((BlankX <= x1 + halfside - 1) && (BlankY > y1 + halfside - 1)){
      TroTwo(x1, y1, halfside);
    }
    //TroThree
    else if((BlankX > x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      TroThree(x1, y1, halfside);
    }
    //TroFour
    else{
      TroFour(x1, y1, halfside);
    }
  }
  else {
    //Blank in top left quadrant
    if((BlankX <= x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      TroOne(x1, y1, halfside);
      SolveBoard(x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(x1,y1,halfside,BlankX,BlankY);
      SolveBoard(x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in top right quadrant
    else if ((BlankX <= x1 + halfside -1) && (BlankY > y1 + halfside -1)){
      TroTwo(x1, y1, halfside);
      SolveBoard(x1,y1+halfside,halfside,BlankX,BlankY);
      SolveBoard(x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in bottom left quadrant
    else if((BlankX > x1 + halfside -1) && (BlankY <= y1 + halfside -1)){
      TroThree(x1, y1, halfside);
      SolveBoard(x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(x1+halfside,y1,halfside,BlankX,BlankY);
      SolveBoard(x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in bottom right quadrant
    else {
      TroFour(x1, y1, halfside);
      SolveBoard(x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(x1+halfside,y1+halfside,halfside,BlankX,BlankY);
    }
  }
}

//Print the board
void gameboard::PrintBoard(){
//  setlocale(LC_ALL, "en_US.UTF-8");
  for (int a = 0; a < boardside; a++){
    for (int b = 0; b < boardside; b++){
      cout << board[a][b];
    }
    cout << '\n';
  }
  delete board;
}

void gameboard::TroOne(int T1X, int T1Y, int T1HS){
      board[T1X+T1HS-1][T1Y+T1HS]=BottomFill;     //2
      board[T1X+T1HS][T1Y+T1HS] = Fill;           //4
      board[T1X+T1HS][T1Y+T1HS-1]=RightFill;      //3
}

void gameboard::TroTwo(int T1X, int T1Y, int T1HS){
      board[T1X+T1HS-1][T1Y+T1HS-1]=BottomFill;   //1
      board[T1X+T1HS][T1Y+T1HS-1]=Fill;	          //3
      board[T1X+T1HS][T1Y+T1HS] = LeftFill;       //4
}

void gameboard::TroThree(int T1X, int T1Y, int T1HS){
      board[T1X+T1HS-1][T1Y+T1HS]=Fill;      	  //2
      board[T1X+T1HS-1][T1Y+T1HS-1]=RightFill;    //1
      board[T1X+T1HS][T1Y+T1HS] = TopFill;        //4
}

void gameboard::TroFour(int T1X, int T1Y, int T1HS){
      board[T1X+T1HS-1][T1Y+T1HS-1]=Fill;         //1
      board[T1X+T1HS-1][T1Y+T1HS]=LeftFill;       //2
      board[T1X+T1HS][T1Y+T1HS-1]=TopFill;        //3
}
