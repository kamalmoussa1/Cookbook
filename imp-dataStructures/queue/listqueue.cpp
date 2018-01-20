#include <iostream>

#include "listqueue.h"
#include "error.h"

#define log(x) (std::cout << x << std::endl) // macro for loggin

namespace IMP
{
  Queue::Queue()
  {
    this->head = NULL;
    this->tail = NULL;
    len = 0;
  }

  Queue::node* Queue::creat_node(int item)
  {
    node* newNode = new node;
    newNode->item = item;
    newNode->next = NULL;

    return newNode;
  }

  bool Queue::isEmpty()
  {
    return this->head == NULL;  
  }

  void Queue::enqueue(int item)
  {
    node* newNode = creat_node(item);

    if(isEmpty())
    {
      this->head = newNode;
      this->tail = newNode;
      len++;

      log("added: " << item); 

    }
    else
    {
      newNode->next = this->head;  // newnode points to previous first node(head)
      this->head    = newNode;     // now head points to the newnode 
      len++;

      log("added: " << item); 
    }

    log("head hold: " << this->head->item);
    log("tail hold: " << this->tail->item);

  }

  int Queue::peek()
  {
    if(isEmpty())
    {
      throw CError("Empty Queue");
      return 0;
    }
    else
      return this->tail->item;
  }

  int Queue::dequeue()
  {
    node* prevNode    = new node;
    node* toDequeueNode = new node; 
 
    prevNode = this->head;

    if(isEmpty()) 
      throw CError("Empty Queue"); 
    else
    {
      while( (prevNode->next != this->tail) && (prevNode->next != NULL) ) // reach the prev node or head
      {
        prevNode = prevNode->next; 
      }

      if(prevNode->next == NULL) // at head
      {
        toDequeueNode = this->head; 
        this->head = NULL;
        len--;
      }
      else
      {
        toDequeueNode  = prevNode->next; // still another node ahead exist
        prevNode->next = NULL; // last node
        this->tail     = prevNode;  
        len--;
      }
      int item = toDequeueNode->item;

      delete toDequeueNode;
      return item; 
    }

  }

  int Queue::size() { return len;}

  void Queue::clearQueue()
  {
    while(!isEmpty())
      dequeue();
  }
  
  Queue::~Queue()
  {
    clearQueue();
    delete head;
    //delete tail; double free! 
  }


}