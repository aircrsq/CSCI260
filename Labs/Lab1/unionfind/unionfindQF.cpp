/************************************************************************
 Design Unit  : Lab1

 File Name    : unionfindQF.cpp

 Purpose      : Union-Find using Quick-find

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
        }   */

        bool Find(int item1, int item2){
            return (Parent[item1] == Parent[item2]);
	    }

        void Union(int Element1, int Element2){
            int Parent = Parent[Element1];
            for (int i=0; i < Parent.length; i++){
                if (Parent[i] == Parent){
                    Parent[i] = Parent[Element2];
                }
            }
        }
}
