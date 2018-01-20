#ifndef LISTQUEUE_H
#define LISTQUEUE_H


namespace IMP
{
  class Queue 
  {
    struct node
    {
      int item;
      node* next;
    };
    int len;
    node* head;
    node* tail; 

    node* creat_node(int item);
  
  public:
    Queue();
    ~Queue();
    void enqueue(int item);
    int  dequeue();
    int  peek();
    void clearQueue();
    bool isEmpty();
    int  size();

  };  
}

#endif