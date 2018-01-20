/*
  Linked-List based stack implementation
*/

#ifndef LISTSTACK_H
#define LISTSTACK_H

namespace IMP
{
  class Stack
  {
    struct node
    {
      int   item;
      node* next;
    };

    node* top;
    int len = 0;

  public:
    Stack();
    ~Stack(); 
    void push(int item);
    int  pop();
    int  peek();
    bool isEmpty();
    int  size(); 
    void clearStack();
  };
}

#endif
