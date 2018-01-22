#ifndef BSTREE_H
#define BSTREE_H

namespace IMP
{
  class BSTree
  {
  public:
    // create tree strucure 
    struct node
    {
      int   item;  // data
      node* left;  // left child
      node* right; // right child
    };

    BSTree();
    BSTree(int item);

    void  insert(int item);
    node* search(int item);

    bool isEmpty();
    int  size();

    node* min();
    node* max(); 

    //traverse tree - Depth-First Search (DFS)
    void traverse(char c ='i');

    
  private:  
    node* root;
    int   count = 0;
   
    node* create_node(int item);
    void  insert(int item, node* parent);
    node* search(int item, node* parent);
    
    // Depth-First Search (DFS)
    node* tr_preorder(node* parent);
    node* tr_inorder(node* parent);
    node* tr_postorder(node* parent);

  };
}






#endif