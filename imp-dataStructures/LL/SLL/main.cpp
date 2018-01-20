#include <iostream>

#include "list.h"

using namespace std;
using namespace IMP;

int main()
{
  List a;

  // add 4 values at the beginning 
  a.add(78);
  a.add(55);
  a.add(4);
  a.add(1);

  a.print();  // print all data

  a.add(14,2); // add 14 at index 2

  a.print();

  a.remove(7); // remove the value at position 4 

  a.print();

  a.remove(a.find(55)); // find 55 and remove it. 

  a.print();

  cout << "Size: " << a.size() << endl; // size of the list i.e no. of items 

  return 0;
}