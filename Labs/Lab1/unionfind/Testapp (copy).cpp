/************************************************************************
 Design Unit  : Lab1

 File Name    : Testapp.cpp

 Purpose      : Test application for unionfind

 Note         : Prompts user for input data filename

 Limitations  : Input data file must be
                   First line - number of elemanets in the array
                   Remaining lines
                      - a small "u" or "f" indicating union or find respectively,
                      followed by a space
                      - an integer within the limits of the array followed
                      by a space
                      - an second integer within the limits of the array,
                      followed by a newline

 Errors       : none known

 Modules      : unionfind.h

 Dependences  : unionfind.h
              : Test input data file
              : iostream
              : fstream
              : string
              : sstream
              : stdlib.h

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Sep 08  New version
*************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include "unionfind.h"

string GetFileName(){
    string FilePath;
    string Prompt;
    system("clear");
    cout << "Please enter path of source file \n";
    cin >> FilePath;
    cout << FilePath << " Is this correct? y/n ";
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
    unionfind da();
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
        unionfind * da = new unionfind(value);
        while (getline(myfile,line)){
            std::istringstream istr(line);
            istr >> operation >> First >> Second;
            if (operation == 'f'){
                clock_t begin = clock();
                da->Find(First, Second);
                clock_t end = clock();
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << elapsed_secs << " for f " << First << '\t' << Second << '\n';
            }
            else if (operation == 'u'){
                clock_t begin = clock();
                da->Union(First, Second);
                clock_t end = clock();
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << elapsed_secs << " for u " << First << '\t' << Second << '\n';
            }
            else if (operation == 'd'){
                da->PrintArray(value);
            }
        }
        myfile.close();
    }
    else {
	cout << "Unable to open file";
    }
    return 0;
}