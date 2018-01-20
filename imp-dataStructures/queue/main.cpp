#include <iostream>

#include "listqueue.h"
#include "error.h"

using namespace std;

int main()
{
  IMP::Queue q;

  q.enqueue(5);
  q.enqueue(4);
  q.enqueue(3);
  q.enqueue(2);
  q.enqueue(1);
  
  cout << "peek: " << q.peek() << endl;
  cout << "size: " << q.size() << endl;

  // q.clearQueue();

  try
  {
    cout <<"Dequeue: " << q.dequeue() << endl;
    cout <<"Dequeue: " << q.dequeue() << endl;
    cout <<"Dequeue: " << q.dequeue() << endl;
    cout <<"Dequeue: " << q.dequeue() << endl;
    cout <<"Dequeue: " << q.dequeue() << endl;
    cout <<"Dequeue: " << q.dequeue() << endl; // nothing to delete 
  }
  catch(const CError & e)
  {
    cout << e.what() << endl;
  }

  return 0;
}