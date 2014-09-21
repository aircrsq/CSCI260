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

int p;
int side, x, y;
char * Fill = "\u2589";
char * RightFill = "\u2590";
char * LeftFill = "\u258B";
char * BottomFill = "\u2586";
char * TopFill = "\u2580";
char * BlankSquare = "\u258F";

    public:
        char *** board;
    gameboard();
    gameboard(int);
	~gameboard();

//  void blank(int, int);

  void PrintBoard(char ***, int);

  void SolveBoard(char ***, int, int, int, int, int);
};

#endif
