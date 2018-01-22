/*
  Print out multiblication table up to 12x12
*/

#include <iostream>

void print_table()
{
  std::cout<<"\t  ";
  for(int j=1; j<13; j++)
    {
      std::cout << j << "\t";
    }
    std::cout << std::endl << "---------------------------------------------------";
                 std::cout << "---------------------------------------------------"  << std::endl;

  for(int i=1; i< 13; i++)
  {
    std::cout << i << "\t";
    for(int j=1; j<13; j++)
    {
      std::cout <<"| " << i*j << '\t';
    }
    std::cout << std::endl;
  }
}

using namespace std;

int main()
{
  print_table();
  return 0;
}