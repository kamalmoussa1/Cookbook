#include <iostream>

#include "list.h"
#include "error.h"

using namespace std;

int main()
{
  IMP::List a;

  // add 4 values at the beginning 
  a.add(78);
  a.add(55);
  a.add(4);
  a.add(1);

  a.print();  // print all data

  a.add(14,2); // add 14 at index 2

  a.print();

  a.print();

try
{
  a.remove(10); // out of bounds 
}
catch(const CError & e)
{
  cout << e.what() << endl;
}

try{
  a.remove(a.find(55)); // find 55 and remove it. 
}
catch (const CError & e)
{
  cout << e.what() << endl;
}

  a.print();

  cout << "Size: " << a.size() << endl; // size of the list i.e no. of items 

  a.clearList();

  cout << "Size after clear: " << a.size() << endl; // size of the list i.e no. of items 

  return 0;
}