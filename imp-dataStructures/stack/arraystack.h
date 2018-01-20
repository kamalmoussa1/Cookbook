/*
  Array-based implementation of Stack for intergers
*/

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "error.h"

namespace IMP
{
  template<int N>
  class AStack
  {
    int arr[N]= {};
    int top = -1;

  public:
    AStack(){}
    void push(int item)
    {
      if(top == N-1)  throw CError("Stack overflow");
      else
      {
       top = top+1; 
       arr[top] = item;
      }
    }
    
    int pop()
    {
      if(isEmpty())
        throw CError("Empty stack");
      else
        return arr[top--];
    }

    int peek()
    {
      if(isEmpty())
        throw CError("Empty stack");
      else
       return arr[top];  
    }

    int size()        { return top+1;     }
    bool isEmpty()    { return top == -1; }
    void clearStack() { top = -1;         }
    ~AStack(){ clearStack(); }

  };

}

#endif