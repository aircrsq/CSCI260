#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Disjoint_Array{
    private:
        int * Parent;
        int * Rank;

    public:
        Disjoint_Array(int Elements){
            Parent = new int [Elements];
            Rank = new int [Elements];
            for (int counter = 0; counter < Elements; counter++){
                Parent[counter] = counter;
                Rank[counter] = 0;
            }
        }

        int Find(int item){
            if (Parent[item] != item){
                Parent[item] = Find(Parent[item]);
            }
            Rank[item] = 1;
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
            for (int count = 0; count < value; count++){
                cout << count << '\t';
            }
            cout << '\n';
            for (int count = 0; count < value; count++){
                cout << Parent[count] << '\t';
            }
            cout << '\n' << '\n';
        }
};

string GetFileName(){
    string FilePath;
    string Prompt;
    cout << "Please enter path of source file \n";
    cin >> FilePath;
    cout << FilePath << " Is this correct?";
    cin >> Prompt;
    if (Prompt == "y"){
        return FilePath;
    }
    else{
        return GetFileName();
    }
}

int main()
{
    Disjoint_Array da();
    string FileName = GetFileName();
    string line;
    int value = 0;
    ifstream myfile (FileName.c_str());
    char operation;
    int First;
    int Second;

    if (myfile.is_open()){
        getline(myfile,line);
        std::istringstream istr(line);
        istr >> value;
        Disjoint_Array * da = new Disjoint_Array(value);
        while (getline(myfile,line)){
            std::istringstream istr(line);
            istr >> operation >> First >> Second;
            if (operation == 'F'){
                cout << da->Find(First) << " is the root of " << First << '\n';
            }
            else if (operation == 'U'){
                da->Union(First, Second);
            }
//            da->PrintArray(value);
        }
//        da->PrintArray(value);
        myfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
