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

  //Setup board
  gameboard::gameboard(){
    cout << "Enter the exponential power for the board. \n";
    cin >> p;
    side =(int)pow((double)2,(double)p);
    /*char *** */board = new char ** [side];
    for (int r=0; r < side; r++){
    board[r] = new char * [side];
  cout << "Please pick two numbers between 1 and " << side << '\n';
  cin >> x >> y;
    board[x-1][y-1] = BlankSquare;
    cout << "Cell " << x << " " << y << " is the blank square. \n";
  }
  }

/*  void blank(int xBlank, int yBlank){
  board[xBlank-1][yBlank-1] = BlankSquare;
  cout << "Cell " << x << " " << y << " is the blank square. \n";
};  */

void gameboard::PrintBoard(char *** b, int side){
  setlocale(LC_ALL, "en_US.UTF-8");
  for (int row = 0; row < side; row++){
    for (int col = 0; col < side; col++){
      cout << b[row][col];
    }
    cout << '\n';
  }
  delete b;
}

void gameboard::SolveBoard(char *** b, int x1, int y1, int side, int BlankX, int BlankY){
  char * Fill = "\u2589";
  char * RightFill = "\u2590";
  char * LeftFill = "\u258B";
  char * BottomFill = "\u2586";
  char * TopFill = "\u2580";
  char * BlankSquare = "\u258F";

  int halfside = side/2;
  if (halfside - 1 == 0){
    //TroOne
    if ((BlankX <= x1 + halfside - 1) && (BlankY > y1 + halfside - 1)){
      b[x1+halfside-1][y1+halfside-1]=BottomFill;   //2
      b[x1+halfside][y1+halfside] = Fill;       //4
      b[x1+halfside][y1+halfside-1]=RightFill;  //3
    }
    //TroTwo
    else if((BlankX <= x1 + halfside -1) && (BlankY <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=BottomFill;     //1
      b[x1+halfside][y1+halfside-1]=Fill;       //3
      b[x1+halfside][y1+halfside] = LeftFill;   //4
    }
    //TroThree
    else if((BlankX > x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=RightFill;  //1
      b[x1+halfside-1][y1+halfside-1]=Fill;     //2
      b[x1+halfside][y1+halfside] = TopFill;    //4
    }
    //TroFour
    else{
      b[x1+halfside-1][y1+halfside-1]=LeftFill; //2
      b[x1+halfside-1][y1+halfside]=Fill;       //1
      b[x1+halfside][y1+halfside-1]=TopFill;    //3
    }
  }
  else {
    //Blank in top right quadrant
    if ((BlankX <= x1 + halfside -1) && (BlankY > y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside-1]=BottomFill;   //1
      b[x1+halfside][y1+halfside-1]=Fill;           //3
      b[x1+halfside][y1+halfside]=LeftFill;         //4
      SolveBoard(b,x1,y1+halfside,halfside,BlankX,BlankY);
      SolveBoard(b,x1,y1,halfside,x1+halfside-1,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1,halfside,x1+halfside,y1+halfside-1);
      SolveBoard(b,x1+halfside,y1+halfside,halfside,x1+halfside,y1+halfside);
    }
    //Blank in top left quadrant
    else if((BlankX <= x1 + halfside - 1) && (BlankY <= y1 + halfside -1)){
      b[x1+halfside-1][y1+halfside]=BottomFill;     //2
      b[x1+halfside][y1+halfside]=Fill;             //4
      b[x1+halfside][y1+halfside-1]=RightFill;      //3
      SolveBoard(b,x1,y1+halfside,halfside,x1+halfside-1,y1+halfside);
      SolveBoard(b,x1,y1,halfside,BlankX,BlankY);
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
