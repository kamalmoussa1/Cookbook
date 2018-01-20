#ifndef LIST_H
#define LIST_H

namespace IMP
{
  class List 
  {
    struct node
    {
      int item;
      node *next;
    };

    node*  head;   // keep track of list's head 
    int len = 0; 
    void clearList();

  public:
    List();
    ~List();

    void add(int item);
    void add(int item, int pos);
    void remove(int pos); 
    int  find(int item); // return pos
    int  size();
    void print();

  };

}

#endif