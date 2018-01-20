#include "list.h"

#include <iostream>

namespace IMP
{
  List::List()
  {
    // create initial node 
    // this->initNode->item = 0;
    // this->initNode->next = nullptr;
    this->head = new node;
    this->head = NULL;
  }

/**
 * @brief At item at the beginning of the list
 * 
 * @param item 
 */
  void List::add(int item) // O(1)
  { 
    // create a new node and initialize its parms 
    node* newNode = new node;
    newNode->item = item;
    newNode->next = NULL;

    // if list is empty 
    if(this->head == NULL)
    {
      this->head = newNode;
      len++;

      std::cout << "Added first element: " << item << std::endl;
    }
    else
    {
      newNode->next = this->head;
      this->head    = newNode; 
      len++;

      std::cout << "Added: " << item << std::endl;
    }
  }

/**
 * @brief Add item at specific position 
 * 
 * @param item 
 * @param pos 
 */
  void List::add(int item, int pos) // O(N)
  {
    node* newNode = new node;
    newNode->item = item;
    newNode->next = NULL;

    if(pos == 0)
    {
      add(item); // add to the front 
    }
    else
    {

    if(this->head == NULL)
    {
      // this->head = newNode; 
    }
    else
    {
      node* prevNode = new node;
      prevNode = this->head;
    
      for (int i = 0; i < pos-1; i++)
      {
        if(prevNode->next != NULL)
          prevNode = prevNode->next;
      }

      newNode->next  = prevNode->next; 
      prevNode->next = newNode;
      std::cout << "Added: " << item << '\n' ; 

      len++; 
    }
    }
  }

/**
 * @brief Remove node at any poistion within litst bounds 
 * 
 * @param pos 
 */
  void List::remove(int pos)    // O(N)
  {
    node* prevNode     = new node;
    node* toRemoveNode = new node;  // to be deleteted 

    prevNode = this->head;
    for(int i=0; i< pos-1; i++)
    {
      if(prevNode->next != NULL) // reach lase node
        prevNode = prevNode->next;
    }
    
    if(prevNode->next == NULL)
    {
      // throw exception(better):: out of bounds 
      std::cout << "Index out of bounds, list size is " << size() << '\n';
      return;
    }

    toRemoveNode = prevNode->next;

    prevNode->next = toRemoveNode->next;
    len--; 

    delete toRemoveNode;

  }

/**
 * @brief Check if a value exists or not 
 * if exist, it returns its position, else returns -1 
 * 
 * @param item 
 * @return int 
 */
  int List::find(int item)
  {
    node* temp = new node;
    temp = this->head;

    for(int i=0; i<len; i++)
    {
      if(temp->item == item)
        return i; // position 
      temp = temp->next;
    }
    delete temp;
    return -1; 
  }

/**
 * @brief Display all the items in the list
 * 
 */
  void List::print()
  {
    node* temp = new node;
    temp = this->head;
 
    while(temp->next != NULL)
    {
      std::cout << " " << temp->item;
      temp = temp->next;
    }  
    std::cout << " " << temp->item << std::endl;

    //delete temp; 
  }

  /**
   * @brief Returns the size of the list, i.e. count of elemetns 
   * 
   * @return int 
   */
  int List::size()
  {
    return len; 
  }

/**
 * @brief Clear the list and free all used memory locations  
 * 
 */
  void List::clearList()
  {
    node* temp = new node;
    while(this->head != NULL)
    {
      temp = this->head;
      head = this->head->next;
      delete temp;
    }
    delete head;
  }

  List::~List()
  {
    clearList();
  }

}