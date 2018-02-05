
#include <iostream>
#include <vector>
#include "issorted_andhow.h"

int main()
{
  using namespace WARS;

  std::vector<int> v1{1,2,3,4,5}; // Yes
  std::vector<int> v2{5,4,3,2,1}; // yes
  std::vector<int> v3{-1,0,1,2,3};// yes
  std::vector<int> v4{1,2,3,0,1}; // no
  std::vector<int> v5{1,2,3,4,1}; // no
  std::vector<int> v6{5,2,3,4,5}; // no

  std::cout << isSortedAndHow(v1) << std::endl;
  std::cout << isSortedAndHow(v2) << std::endl;
  std::cout << isSortedAndHow(v3) << std::endl;
  std::cout << isSortedAndHow(v4) << std::endl; 
  std::cout << isSortedAndHow(v5) << std::endl; 
  std::cout << isSortedAndHow(v6) << std::endl; 


  std::string a = isSortedAndHow({});


  return 0;
}


// run: g++ -std=c++0x main.cpp -o main && ./main && rm main 