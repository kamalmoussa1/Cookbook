/*
  Array-based implementation of Stack for intergers
*/

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H


namespace IMP
{
  template<int N>
  class AStack
  {ا   
    int arr[N]= {};
    int top = -1;

  public:
    AStack(){}
    void push(int item)
    {
      if(top == size()) {std::cout << "Overflow\n"; return; }
      else{ top = top+1; arr[top]= item;}
    }
    int pop()
    {
      if(isEmpty()){std::cout << "Empty: "; return -1;} 
      else { return arr[top--];}
    }

    int peek()        { return arr[top];  }
    int size()        { return top+1;     }
    bool isEmpty()    { return top == -1; }
    void clearStack() { top = -1;         }
    ~AStack(){ clearStack(); }

  };

}

#endif