#include <iostream>

#include "bstree.h"
#include "error.h"

#define log(x) (std::cout << x << std::endl)

namespace IMP
{
  BSTree::BSTree()
  { 
    this->root = new node;
    this->root = NULL;
  }

  BSTree::BSTree(int item)
  { 
    this->root = create_node(item);
  }

  BSTree::node* BSTree::create_node(int item)
  {
    node* _node = new node;
    _node->item = item;
    _node->left = NULL;
    _node->right= NULL;

    return _node;
  } 

  void BSTree::insert(int item, node* parent)  
  {
    node* new_node = create_node(item); // a node with no childern

    if(item < parent->item) // add to left
    { 
      if(parent->left != NULL) // no left node
      {
        insert(item, parent->left);
      }
      else
      {
        parent->left = new_node; 
        log("added to left");
      }
    }
    else // add to right
    {
      if(parent->right != NULL) // no left node
      {
        insert(item, parent->right);
      }
      else
      {
        parent->right = new_node; 
        log("added to right");
      } 
  
    }
  }

  void BSTree::insert(int item) // O( log(h) )
  {
    if(root != NULL)
      insert(item, root);
    else
    {
      this->root = create_node(item);
      log("root node");
    }
    count++;
  }

  BSTree::node* BSTree::search(int item, node* parent)
  {
    if (item == parent->item)
      return parent;

    else if (item < parent->item)
      search(item, parent->left);
    else 
      search(item, parent->right);
  }

  BSTree::node* BSTree::search(int item) // O( log(h) )
  {
    if(isEmpty()) 
    {
      throw CError("Empty tree");
      return NULL;
    }
    if(item == root->item)
      return root;
    else
      search(item, root);
  }

  BSTree::node* BSTree::min()
  {
    if(isEmpty())
    {
      throw CError("Empty tree");
    }
    else
    {
      node* temp = this->root;

      while(temp->left != NULL) // find the deepest leftmost node
      {
        temp = temp->left;
      }
      
      return temp;

    }
  }

  BSTree::node* BSTree::max()
  {
    if(isEmpty())
    {
      throw CError("Empty tree");
    }
    else
    {
      node* temp = this->root;

      while(temp->right != NULL) // find the deepest leftmost node
      {
        temp = temp->right;
      }
  
      return temp;

    }
  }

  BSTree::node* BSTree::tr_preorder(node* parent)
  {
    std::cout << parent->item << " ";

    if(parent->left != NULL)
      tr_preorder(parent->left);

    if(parent->right != NULL)
      tr_preorder(parent->right);
  }

  BSTree::node* BSTree::tr_inorder(node* parent)
  {
    if(parent->left != NULL)
      tr_inorder(parent->left);
    
    std::cout << parent->item << " ";

    if(parent->right != NULL)
      tr_inorder(parent->right);
  }
  BSTree::node* BSTree::tr_postorder(node* parent)
  {
    if(parent->left != NULL)
      tr_postorder(parent->left);

    if(parent->right != NULL)
      tr_postorder(parent->right);
    
    std::cout << parent->item << " ";
  }

  void BSTree::traverse(char c)
  {
    if(isEmpty())
    {
      throw CError("Empty Tree");
      return;
    }

    switch (c)
    {
      case 'i':
        tr_inorder(this->root);
        break;
      case 'p':
        tr_preorder(this->root);
        break;
      case 's':  
        tr_postorder(this->root);
        break;
      default:
        tr_inorder(this->root);
        break;
    }
    std::cout << std::endl; // break line
  }

  bool BSTree::isEmpty()
  {
   return this->root == NULL; 
  }

  int BSTree::size()
  {
    return count; 
  }
  
}