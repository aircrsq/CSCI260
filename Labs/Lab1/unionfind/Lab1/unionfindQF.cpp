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
#include <iostream>
#include <stdlib.h>
#include "unionfind.h"


unionfind::unionfind(int Elements){
  elements = Elements;
  Parent = new int [Elements];
  for (int counter = 0; counter < Elements; counter++){
    Parent[counter] = counter;
  }
}

int unionfind::Root(int item){
  if (Parent[item] != item){
    Parent[item] = Root(Parent[item]);
  }
  return Parent[item];
}

bool unionfind::Find(int item1, int item2){
  return (Root(item1) == Root(item2));
}

void unionfind::Union(int Element1, int Element2){
  int ParentElement = Parent[Element1];
  for (int i=0; i < elements; i++){
    if (Parent[i] == ParentElement){
      Parent[i] = Parent[Element2];
    }
  }
}

void unionfind::PrintArray(int value){
  system("clear");
  for (int count = 0; count < value; count++){
    std::cout << count << '\t';
  }
  std::cout << '\n';
  for (int count = 0; count < value; count++){
    std::cout << Parent[count] << '\t';
  }
  std::cout << '\n' << '\n';
}
