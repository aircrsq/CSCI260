#ifndef __unionfind_h__
#define __unionfind_h__
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

using namespace std;

class unionfind{

    public:
        int n;
        int * Parent;
        int * Rank;
        int elements;


	unionfind(int);
	~unionfind();

        int Root(int);

        bool Find(int, int);

        void Union(int, int);

        void PrintArray(int);
};

#endif
