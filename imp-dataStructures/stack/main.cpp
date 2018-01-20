#include <iostream>

#include "liststack.h"
#include "arraystack.h"
using namespace std;

int main()
{
  IMP::AStack<5> s; // array-based stack
  IMP::Stack sList; // List-based  stack 


  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);

  cout << "Size: " << s.size() << endl;

  cout << "Peek: " << s.peek() << endl; // top element 

  cout << s.pop() << endl;
  cout << s.pop() << endl;

  cout << "Peek: " << s.peek() << endl;

  cout << s.pop() << endl;
  cout << s.pop() << endl;

  cout << s.pop() << endl;  // pop from empty stack- return -1 for now 


 // s.clearStack(); // delete all elements 

  cout << "Size: " << s.size()    << endl;
 


  return 0;
}