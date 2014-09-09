/************************************************************************
 Design Unit  : Lab1

 File Name    : unionfindQU.cpp

 Purpose      : Union-Find using Quick-Union

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

class unionfind{
    private:
        int * Parent;
        int * Rank;

    public:
        unionfind(int Elements){
            Parent = new int [Elements];
            for (int counter = 0; counter < Elements; counter++){
                Parent[counter] = counter;
            }
        }

        int Root(int item){
            while (item != Parent[item]){
                item = Parent[item];
            }
            return item;
        }

        bool Find(int item1, int item2){
            return (Root(item1) == Root(item2));
	    }

        void Union(int Element1, int Element2){
            int i = Root(Element1);
            int j = Root(Element2);
            Parent[i] = j;
        }
}
