#include <iostream>

#include "liststack.h"

using namespace std;

int main()
{
  IMP::Stack s;

  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);

  cout << s.isEmpty() << endl; // 0:false 
  cout << s.size()    << endl;

  cout << "Peek: " << s.peek() << endl;

  cout << s.pop() << endl;
  cout << s.pop() << endl;

  cout << "Peek: " << s.peek() << endl;

  cout << s.pop() << endl;
  cout << s.pop() << endl;


  // s.clearStack(); // delete all elements 

  cout << "Size: " << s.size()    << endl;


  return 0;
}