#include <iostream>

#include "bstree.h"
#include "error.h"

using namespace std;


int main()
{
  IMP::BSTree bt;
  
  bt.insert(7 );  // root
  bt.insert(5);  // left
  bt.insert(10); // right
  bt.insert(11); // right-right
  bt.insert(4);  // left-left
  bt.insert(3);  // left-left-right
  bt.insert(8);  // right-left 
  bt.insert(6);   // left-right 

try
{
  IMP::BSTree::node* st =  bt.search(5);  // a reference to the node that hold 5

  IMP::BSTree::node* min = bt.min();     // a reference to the minimum 
  IMP::BSTree::node* max = bt.max();     // a reference to the maximum 

  cout <<"Min: " << min->item << endl; 
  cout <<"Max: " << max->item << endl;

  cout << "Inorder   display: ";
    bt.traverse();    // default is inorder

  cout << "Inorder   display: ";
    bt.traverse('i'); // i for inorder

  cout << "Preorder  display: ";
    bt.traverse('p'); // p for preorder

  cout << "Postorder display: ";
    bt.traverse('s'); // s for postorder 
}
catch( const CError & e)
{
  cout << e.what() << endl;
}

 cout <<"Size: " << bt.size() << endl;
  
  return 0;  
}
