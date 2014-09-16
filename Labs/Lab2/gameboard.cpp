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

gameboard::gameboard(int side){
  for (int r=0; r < side; r++){
    board[r] = new char * [side];
  }
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
}
