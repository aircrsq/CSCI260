#ifndef __gameboard_h__
#define __gameboard_h__
/************************************************************************
 Design Unit  : Lab1

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
        char *** board;
    public:

	gameboard(int);
	~gameboard();

  void PrintBoard(char ***, int);

  void SolveBoard(char ***, int, int, int, int, int);
};

#endif
