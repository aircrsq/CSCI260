#include "skiplists.hpp"
#include <iostream>

using namespace AG;

int main(){

  skiplist<int, int> sl;  
  
  std::cerr << "created" << std::endl;

  unsigned int max = 100000;
  // unsigned int max = 2;


  for (unsigned int i = 0; i < max; i++){
    sl.insert(i, i);
    std::cerr << "inserted key=" << i << " value=" << i << std::endl;
  }

  for (unsigned int i = 0; i < max; i++){

    if (i!=sl.search(i))
      std::cerr << "search error for key=" << i << std::endl;
    else
      std::cerr << "key=" << i << " value=" << i << std::endl;      
  }

  sl.remove(1);
  sl.remove(10);

  for (unsigned int i = 0; i < max; i++){

    if (i!=sl.search(i))
      std::cerr << " after removing key=" << i << " not there"<< std::endl;
  }

}
