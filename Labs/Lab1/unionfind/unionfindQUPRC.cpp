/************************************************************************
 Design Unit  : Lab1

 File Name    : unionfindQUPRC.cpp

 Purpose      : Best algorithm for Union-Find incorporating compression

 Note         :

 Limitations  :

 Errors       : none known

 Modules      : unionfind.h

 Dependences  : none

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 08  New version
*************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "unionfind.h"

class unionfind{
    private:
        int * Parent;
        int * Rank;

    public:
        unionfind::unionfind(int Elements){
            Parent = new int [Elements];
            Rank = new int [Elements];
            for (int counter = 0; counter < Elements; counter++){
                Parent[counter] = counter;
                Rank[counter] = 0;
            }
        }

        int Root(int item){
            if (Parent[item] != item){
                Parent[item] = Root(Parent[item]);
            }
            if (Parent[item] == item){
                Rank[item] = 0;
            }
            else {
                Rank[item] = 1;
            }
                return Parent[item];
        }

        bool Find(int item1, int item2){
            return (Root(item1) == Root(item2));
        }

        void Union(int Element1, int Element2){
            if (!(Find(Element1, Element2))){
                if (Rank[Element1] < Rank[Element2]){
                    Parent[Element1] = Root(Element2);
                    Rank[Element1]++;
                }
                else{
                    Parent[Element2] = Root(Element1);
                    Rank[Element2]++;
                }
            }
        }

        void PrintArray(int value){
	    system("clear");
            for (int count = 0; count < value; count++){
                std::cout << count << '\t';
            }
            std::cout << '\n';
            for (int count = 0; count < value; count++){
                std::cout << Parent[count] << '\t';
            }
            std::cout << '\n';
            for (int count = 0; count < value; count++){
                std::cout << Rank[count] << '\t';
            }
            std::cout << '\n' << '\n';
        }

};