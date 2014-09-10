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
#ifndef unionfind
#define unionfind




class unionfind{
    private:
        int n;
        int * Parent;
        int * Rank;

    public:
        unionfind(int Elements);

        bool Find(int item1, int item2);

        void Union(int Element1, int Element2);

        void PrintArray(int value);
};
#endif
