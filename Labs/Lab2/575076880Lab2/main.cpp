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
 1.0          DB      Sep 15  New version
*************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "gameboard.h"
#include "math.h"

using namespace std;

void PrintBoard(char ***, int);

void SolveBoard(char ***, int, int, int, int, int);

int main(){
  int n;
  int k;
  int i,j;
  char * BlankSquare = "\u2592";

  //Setup board
  cout << "Enter the width of your screen, for printing (in characters):";
  cin >> n;
  cout << "Enter the power k, making a chessboard 2^k x 2^k;";
  cin >> k;
  int side =(int)pow((double)2,(double)k);
  char *** board = new char ** [side];
  for (int r=0; r < side; r++){
    board[r] = new char * [side];
  }

  //Get blank square
  cout << "Enter the row and column of the missing square, separated by a space:";
  cin >> i >> j;
  board[i-1][j-1] = BlankSquare;
  cout << "Cell " << i << " " << j << " is the blank square. \n";

  //Solve board
  SolveBoard(board, 0, 0, side, i-1, j-1);

  //Display board
  PrintBoard(board, side);
//  system("pause");
  return 0;
}

void PrintBoard(char *** b, int side){
  setlocale(LC_ALL, "en_US.UTF-8");
  for (int row = 0; row < side; row++){
    for (int col = 0; col < side; col++){
      cout << b[row][col];
    }
    cout << '\n';
  }
  delete b;
}

void SolveBoard(char *** b, int x1, int y1, int side, int BlankX, int BlankY){
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
      b[x1+halfside-1][y1+halfside]=BottomFill;     //2
      b[x1+halfside][y1+halfside] = Fill;           //4
      b[x1+halfside][y1+halfside-1]=RightFill;      //3
    }
    //TroTwo
    else if ((BlankX <= x1 + halfside - 1) && (BlankY > y1 + halfside - 1)){
      b[x1+halfside-1][y1+halfside-1]=BottomFill;   //1
      b[x1+halfside][y1+halfside-1]=Fill;	    //3
      b[x1+halfside][y1+halfside] = LeftFill;       //4
    }
    //TroThree
    else if((BlankX > x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=Fill;      	    //2
      b[x1+halfside-1][y1+halfside-1]=RightFill;    //1
      b[x1+halfside][y1+halfside] = TopFill;        //4
    }
    //TroFour
    else{
      b[x1+halfside-1][y1+halfside-1]=Fill;         //1
      b[x1+halfside-1][y1+halfside]=LeftFill;       //2
      b[x1+halfside][y1+halfside-1]=TopFill;        //3
    }
  }
  else {
    //Blank in top left quadrant
    if((BlankX <= x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=BottomFill;     //2
      b[x1+halfside][y1+halfside]=Fill;             //4
      b[x1+halfside][y1+halfside-1]=RightFill;      //3
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,BlankX,BlankY);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in top right quadrant
    else if ((BlankX <= x1 + halfside -1) && (BlankY > y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside-1]=BottomFill;   //1
      b[x1+halfside][y1+halfside-1]=Fill;           //3
      b[x1+halfside][y1+halfside]=LeftFill;         //4
      SolveBoard(b,x1,y1+halfside,halfside,BlankX,BlankY);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in bottom left quadrant
    else if((BlankX > x1 + halfside -1) && (BlankY <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside-1]=RightFill;    //1
      b[x1+halfside-1][y1+halfside]=Fill;           //2
      b[x1+halfside][y1+halfside]=TopFill;          //4
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,BlankX,BlankY);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in bottom right quadrant
    else {
      b[x1+halfside-1][y1+halfside-1]=Fill;         //1
      b[x1+halfside-1][y1+halfside]=LeftFill;       //2
      b[x1+halfside][y1+halfside-1]=TopFill;        //3
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,BlankX,BlankY);
    }
  }
}

/*
using namespace std;

void PrintBoard(char ***, int);

void SolveBoard(char ***, int, int, int, int, int);

int main(){
  int n;
  int p;
  int x,y;
  char * BlankSquare = "\u258F";

  //Setup board
  cout << "Enter the exponential power for the board. \n";
  cin >> p;
  int side =(int)pow((double)2,(double)p);
  char *** board = new char ** [side];
  for (int r=0; r < side; r++){
    board[r] = new char * [side];
  }

  //Get blank square
  cout << "Please pick two numbers between 1 and " << side << '\n';
  cin >> x >> y;
  board[x][y] = BlankSquare;
  cout << "Cell " << x+1 << " " << y+1 << " is the blank square. \n";

  //Solve board
  SolveBoard(board, 0, 0, side, x, y);

  //Display board
  PrintBoard(board, side);
  system("pause");
  return 0;
}
/*
void PrintBoard(char *** b, int side){
  setlocale(LC_ALL, "en_US.UTF-8");
  for (int row = 0; row < side; row++){
    for (int col = 0; col < side; col++){
      cout << b[row][col];
    }
    cout << '\n';
  }
  delete b;
}

void SolveBoard(char *** b, int x1, int y1, int side, int x, int y){
  char * Fill = "\u2589";
  char * RightFill = "\u2590";
  char * LeftFill = "\u258B";
  char * BottomFill = "\u2586";
  char * TopFill = "\u2580";
  char * BlankSquare = "\u258F";

  int halfside = side/2;
  if (halfside - 1 == 0){
    if ((x <= x1 + halfside - 1) && (y > y1 + halfside - 1)){
      b[x1+halfside-1][y1+halfside-1]=BottomFill;   //2
      b[x1+halfside][y1+halfside] = Fill;       //4
      b[x1+halfside][y1+halfside-1]=RightFill;  //3
    }
    else if((x <= x1 + halfside -1) && (y <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=BottomFill;     //1
      b[x1+halfside][y1+halfside-1]=Fill;       //3
      b[x1+halfside][y1+halfside] = LeftFill;   //4
    }
    else if((x > x1 + halfside - 1) && (y <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=RightFill;  //1
      b[x1+halfside-1][y1+halfside-1]=Fill;     //2
      b[x1+halfside][y1+halfside] = TopFill;    //4
    }
    else{
      b[x1+halfside-1][y1+halfside-1]=LeftFill; //2
      b[x1+halfside-1][y1+halfside]=Fill;       //1
      b[x1+halfside][y1+halfside-1]=TopFill;    //3
    }
  }
  else {
    if ((x <= x1 + halfside -1) && (y > y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside-1]=TopFill;  //2
      b[x1+halfside][y1+halfside]=Fill;         //4
      b[x1+halfside][y1+halfside-1]=RightFill;  //3
      SolveBoard(b,x1,y1+halfside,halfside,x,y);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    else if((x <= x1 + halfside - 1) && (y <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=BottomFill; //1
      b[x1+halfside][y1+halfside-1]=Fill;       //3
      b[x1+halfside][y1+halfside]=RightFill;    //4
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,x,y);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    else if((x > x1 + halfside -1) && (y <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside-1]=Fill;     //2
      b[x1+halfside-1][y1+halfside]=RightFill;  //1
      b[x1+halfside][y1+halfside]=TopFill;      //4
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,x,y);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    else {
      b[x1+halfside-1][y1+halfside-1]=LeftFill; //2
      b[x1+halfside-1][y1+halfside]=Fill;       //1
      b[x1+halfside][y1+halfside-1]=TopFill;    //3
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x,y);
    }
  }
}   */
/*  char *** board;
  board = new char**[2];
	board[0][0] = Fill;
	board[0][1] = LeftFill;
	board[1][0] = TopFill;
	board[1][1] = BlankSquare;
  for (int i = 0; i <= 1; i++){
    for (int j = 0; j <= 1; j++){
      cout << board[i][j];
    }
    cout << endl;
  } */