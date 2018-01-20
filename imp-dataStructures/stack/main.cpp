#include <iostream>

#include "liststack.h"
#include "arraystack.h"
using namespace std;

int main()
{
  IMP::AStack<4> s; // array-based stack
  //IMP::Stack s; // List-based  stack 

try
{
  // s.peek();  // no data- Empty stack thrown
  s.push(1); 
  s.push(2);
  s.push(3);
  s.push(4);

  // stack overflow 
  
  cout << "Size: " << s.size() << endl;

  cout << "Peek: " << s.peek() << endl; // top element 

  cout << s.pop() << endl;
  cout << s.pop() << endl;

  cout << "Peek: " << s.peek() << endl;

  cout << s.pop() << endl;
  cout << s.pop() << endl;

  cout << s.pop() << endl;  // pop from empty stack- ERROR thrown 


 // s.clearStack(); // delete all elements 

  cout << "Size: " << s.size()    << endl;

}
catch (const CError & e)
{
  std::cout << e.what() << std::endl;
}


  return 0;
}