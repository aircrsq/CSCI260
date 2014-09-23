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
 1.1	      DB      Sep 19  Unicode for symbols changed for better
			      presentation
*************************************************************************/

class gameboard{
  private:
    int n, k;
    int p;
    int x, y;
    char * Fill = "\u2588";
    char * RightFill = "\u25C0";
    char * LeftFill = "\u25B6";
    char * BottomFill = "\u25B2";
    char * TopFill = "\u25BC";
    char * BlankSquare = "\u2592";
    char *** board;

    //Make Tromino one
    void TroOne(int, int, int);

    //Make Tromino two
    void TroTwo(int, int, int);

    //Make Tromino three
    void TroThree(int, int, int);

    //Make Tromino four
    void TroFour(int, int, int);

  public:
    int boardside, i, j;
    gameboard();
    gameboard(int);
    ~gameboard();

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
