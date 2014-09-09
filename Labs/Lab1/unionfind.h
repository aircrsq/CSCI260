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
        unionfind(int Elements);/*{
            Parent = new int [Elements];
            Rank = new int [Elements];
            for (int counter = 0; counter < Elements; counter++){
                Parent[counter] = counter;
                Rank[counter] = 0;
            }
        }       */

/*        int Root(int item){
            if (Parent[item] != item){
                Parent[item] = Find(Parent[item]);
            }
            if (Parent[item] == item){
		Rank[item] = 0;
	    }
	    else {
		Rank[item] = 1;
	    }
            return Parent[item];
       }        */

        bool Find(int item1, int item2);

        void Union(int Element1, int Element2);

        void PrintArray(int value);
};
#endif
