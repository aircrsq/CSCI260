#ifndef __gameboard_h__
#define __gameboard_h__
/************************************************************************
 Design Unit  : Lab2

 File Name    : gameboard.h

 Purpose      : Header file for gameboard

 Note         :

 Limitations  :

 Errors       : none known

 Modules      :

 Dependences  : none

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 16  New version
*************************************************************************/

class gameboard{
    private:
int n, i, j, k;
int p;
int side, x, y;
char * Fill = "\u2588";
char * RightFill = "\u25C0";
char * LeftFill = "\u25B6";
char * BottomFill = "\u25B2";
char * TopFill = "\u25BC";
char * BlankSquare = "\u2592";
char *** board;

    public:
    gameboard();
    gameboard(int);
	~gameboard();

//  void blank(int, int);

  //Setup the board
  void SetupBoard();

  //Get the blank square
  void GetBlankSquare();

  //Solve the board
  void SolveBoard(int, int, int, int, int);

  //Print the board
  void PrintBoard();
};

#endif

