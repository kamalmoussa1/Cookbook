#include <iostream>

#include "liststack.h"
#include "error.h"

namespace IMP
{
  Stack::Stack()
  {
    top = new node;
    top = NULL;
  }

  void Stack::push(int item)
  {
    node* newNode = new node;
    newNode->item = item;
    newNode->next = NULL;

    // if empty list
    if(isEmpty())
    {
      this->top = newNode;
      len++;
    }
    else
    {
      newNode->next = this->top; 
      this->top     = newNode; 
      len++;
    }

  }

  int Stack::peek()
  {
    if(isEmpty())
      throw CError("Empty Stack"); 
    else 
      return this->top->item;
  }

  int Stack::pop()
  {
    int item; 
    node* currentNode = new node;
    currentNode = this->top;

    if(isEmpty()) 
      throw CError("Empty Stack");
    else
    {
      this->top = this->top->next;
      len--;

      item = currentNode->item;
    }

    delete currentNode;

    return item;
  }

  bool Stack::isEmpty()
  {
    return this->top == NULL;
  }

  int Stack::size()
  {
    return len;
  }


  void Stack::clearStack()
  {
    while(!isEmpty())
    {
      pop();
    }
  }

  Stack::~Stack()
  {
    clearStack();
    delete top; 
  }
}
