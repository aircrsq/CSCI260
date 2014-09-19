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
  int p;
  int x,y;
/*    char * Fill = "\u2589";
  char * RightFill = "\u2590";
  char * LeftFill = "\u258B";
  char * BottomFill = "\u2586";
  char * TopFill = "\u2580";    */
  char * BlankSquare = "\u258F";

  //setlocale(LC_ALL, "en_US.UTF-8");

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
