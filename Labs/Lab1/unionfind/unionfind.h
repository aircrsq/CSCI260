/************************************************************************
 Design Unit  : Lab1

 File Name    : unionfind.h

 Purpose      : Header file for unionfind

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
 1.0          DB      Sep 08  New version
*************************************************************************/
#ifndef ___UNIONFIND___
#define ___UNIONFIND___

#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
#include <stdlib.h>

using namespace std;

class unionfind{
    private:
        int n;
        int * Parent;
        int * Rank;

    public:
        unionfind(int);

        bool Find(int, int);

        void Union(int, int);

        void PrintArray(int);
};
#endif
