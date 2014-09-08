#ifndef unionfind
#define unionfind




class unionfind{
    private:
        int n;
	int * Parent;
        int * Rank;

    public:
        unionfind(int Elements){
            Parent = new int [Elements];
            Rank = new int [Elements];
            for (int counter = 0; counter < Elements; counter++){
                Parent[counter] = counter;
                Rank[counter] = 0;
            }
        }

        int Root(int item){
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
       }

       int Find(int item){
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
        }

        void Union(int Element1, int Element2){
            if (Find(Element1) != Find(Element2)){
                if (Rank[Element1] < Rank[Element2]){
                    Parent[Element1] = Find(Element2);
                    Rank[Element1]++;
                }
                else{
                    Parent[Element2] = Find(Element1);
                    Rank[Element2]++;
                }
            }
            else
                cout << Element1 << " and " << Element2 << " are in the same bush\n";
        }

        void PrintArray(int value){
	    system("clear");
            for (int count = 0; count < value; count++){
                cout << count << '\t';
            }
            cout << '\n';
            for (int count = 0; count < value; count++){
                cout << Parent[count] << '\t';
            }
            cout << '\n';
            for (int count = 0; count < value; count++){
                cout << Rank[count] << '\t';
            }
            cout << '\n' << '\n';
        }
};
