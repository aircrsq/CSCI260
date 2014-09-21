/************************************************************************
 Design Unit  : Lab2

 File Name    : gameboard.cpp

 Purpose      :

 Note         :

 Limitations  :

 Errors       : none known

 Modules      : gameboard.h

 Dependences  : none

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 16  New version
*************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "gameboard.h"
#include "math.h"

using namespace std;

int n, i, j, k;
int p;
int boardside, x, y;
char * Fill = "\u2588";
char * RightFill = "\u25C0";
char * LeftFill = "\u25B6";
char * BottomFill = "\u25B2";
char * TopFill = "\u25BC";
char * BlankSquare = "\u2592";
char *** board;

//Constructor
gameboard::gameboard(){
  cout << "Enter the width of your screen, for printing (in characters):";
  cin >> n;
  cout << "Enter the power k, making a chessboard 2^k x 2^k;";
  cin >> k;
  int side =(int)pow((double)2,(double)k);
  board = new char ** [side];
  for (int r=0; r < side; r++){
    board[r] = new char * [side];
  }
}

//Setup board
void gameboard::SetupBoard(){
  cout << "Enter the width of your screen, for printing (in characters):";
  cin >> n;
  cout << "Enter the power k, making a chessboard 2^k x 2^k;";
  cin >> k;
  int side =(int)pow((double)2,(double)k);
  char *** board = new char ** [side];
  for (int r=0; r < side; r++){
    board[r] = new char * [side];
  }
}

//Get Blank Square
void gameboard::GetBlankSquare(){
  char * BlankSquare = "\u2592";
  cout << "Enter the row and column of the missing square, separated by a space:";
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
      board[x1+halfside-1][y1+halfside]=BottomFill;     //2
      board[x1+halfside][y1+halfside] = Fill;           //4
      board[x1+halfside][y1+halfside-1]=RightFill;      //3
    }
    //TroTwo
    else if ((BlankX <= x1 + halfside - 1) && (BlankY > y1 + halfside - 1)){
      board[x1+halfside-1][y1+halfside-1]=BottomFill;   //1
      board[x1+halfside][y1+halfside-1]=Fill;	        //3
      board[x1+halfside][y1+halfside] = LeftFill;       //4
    }
    //TroThree
    else if((BlankX > x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      board[x1+halfside-1][y1+halfside]=Fill;      	    //2
      board[x1+halfside-1][y1+halfside-1]=RightFill;    //1
      board[x1+halfside][y1+halfside] = TopFill;        //4
    }
    //TroFour
    else{
      board[x1+halfside-1][y1+halfside-1]=Fill;         //1
      board[x1+halfside-1][y1+halfside]=LeftFill;       //2
      board[x1+halfside][y1+halfside-1]=TopFill;        //3
    }
  }
  else {
    //Blank in top left quadrant
    if((BlankX <= x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      board[x1+halfside-1][y1+halfside]=BottomFill;     //2
      board[x1+halfside][y1+halfside]=Fill;             //4
      board[x1+halfside][y1+halfside-1]=RightFill;      //3
      SolveBoard(x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(x1,y1,halfside,BlankX,BlankY);
      SolveBoard(x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in top right quadrant
    else if ((BlankX <= x1 + halfside -1) && (BlankY > y1 + halfside -1)){
      board[x1+halfside-1][y1+halfside-1]=BottomFill;   //1
      board[x1+halfside][y1+halfside-1]=Fill;           //3
      board[x1+halfside][y1+halfside]=LeftFill;         //4
      SolveBoard(x1,y1+halfside,halfside,BlankX,BlankY);
      SolveBoard(x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in bottom left quadrant
    else if((BlankX > x1 + halfside -1) && (BlankY <= y1 + halfside -1)){
      board[x1+halfside-1][y1+halfside-1]=RightFill;    //1
      board[x1+halfside-1][y1+halfside]=Fill;           //2
      board[x1+halfside][y1+halfside]=TopFill;          //4
      SolveBoard(x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(x1+halfside,y1,halfside,BlankX,BlankY);
      SolveBoard(x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in bottom right quadrant
    else {
      board[x1+halfside-1][y1+halfside-1]=Fill;         //1
      board[x1+halfside-1][y1+halfside]=LeftFill;       //2
      board[x1+halfside][y1+halfside-1]=TopFill;        //3
      SolveBoard(x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(x1+halfside,y1+halfside,halfside,BlankX,BlankY);
    }
  }
}

//Print the board
void gameboard::PrintBoard(){
  setlocale(LC_ALL, "en_US.UTF-8");
  for (int row = 0; row < boardside; row++){
    for (int col = 0; col < boardside; col++){
      cout << board[row][col] << boardside;
    }
    cout << '\n';
  }
  delete board;
}
