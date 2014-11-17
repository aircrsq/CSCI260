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
#include <iostream>
#include <stdlib.h>
#include "unionfind.h"

unionfind::unionfind(int Elements){
  Parent = new int [Elements];
  for (int counter = 0; counter < Elements; counter++){
    Parent[counter] = counter;
  }
}

int unionfind::Root(int item){
  while (item != Parent[item]){
    item = Parent[item];
  }
  return item;
}

bool unionfind::Find(int item1, int item2){
  return (Root(item1) == Root(item2));
}

void unionfind::Union(int Element1, int Element2){
  int i = Root(Element1);
  int j = Root(Element2);
  Parent[i] = j;
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
