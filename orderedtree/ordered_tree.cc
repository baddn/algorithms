//-----------------------------------------------------------------------------
// File: ordered_tree.h
// Purpose: Implementation of an ordered tree which support deletes by ordered statistic
// Example: Delete the Nth smallest and return
// Author: Baddn
//------------------------------------------------------------------------------

#include <iostream>
#include <string.h>
#include "ordered_tree.h"

using namespace std;

//--------------------
// OrderedTree()
// Class Constructor
//--------------------

OrderedTree::OrderedTree()
{
  root = NULL;
  return;
}

//-------------------------------------------
// InsertValue()
// Inserts a node representing the specified 
// value in the tree
//-------------------------------------------

void OrderedTree::InsertValue(int value)
{
  if(root == NULL)
  {
    OrderedTreeNode *node = new OrderedTreeNode();
    node->value = value;
    node->subtree_count = 0;
    node->left = NULL;
    node->right = NULL;
    root = node;
  }
  else
  {
    InsertIntoTree(root, value);
  }
}

//----------------------------------------
// InsertIntoTree
// Insert the value to the tree rooted at
// node
//-----------------------------------------

void OrderedTree::InsertIntoTree(OrderedTreeNode *&node, int value)
{
  if(NULL == node)
  {
    node = new OrderedTreeNode();
    node->value = value;
    node->subtree_count= 0;
    node->left = NULL;
    node->right= NULL;

    return;
  }

  // Recursively insert into tree
  if(value <= node->value)
  {
    node->subtree_count++;
    InsertIntoTree(node->left, value);
  }
  else
  {
    node->subtree_count++;
    InsertIntoTree(node->right, value);
  }
}

//--------------------------------------
// PrintTree
// Print the contents of the tree
//--------------------------------------

void OrderedTree::PrintTree()
{
  PrintNodes(root);
}

//--------------------------------------
// PrintNodes
// Print the contents of entire 
// the tree
//--------------------------------------

void OrderedTree::PrintNodes(OrderedTreeNode *node)
{
  if(NULL != node)
  {
    PrintNodes(node->left);
    cout << node->value << " " << node->subtree_count << "\n";
    PrintNodes(node->right);
  }
}

//--------------------------------------
// DeleteByValue
// Delete node corressponding to the
// value from the tree
//--------------------------------------

void OrderedTree::DeleteByValue(int value)
{
  DeleteFromTree(root, value);
}

//--------------------------------------
// DeleteNode
// Delete node corressponding to the
// value from the tree
//--------------------------------------

void OrderedTree::DeleteNode(OrderedTreeNode *&node)
{

  // Case 1. It's a leaf Node
  if(node->left == NULL && node->right == NULL)
  {
    delete node;
    node = NULL;
    return;
  } 

  // Case 2: Node has only one child
  if(node->left == NULL || node->right == NULL)
  {
    OrderedTreeNode *temp = node;
    if(node->left == NULL)
    {
      node = node->right;
    } 
    else
    {
      node = node->left;
    }  
    delete temp;
    return;
  }

  // Case 3: Node has two children
  OrderedTreeNode *& succ = SuccessorNode(node->right);
  node->value = succ->value;
  node->subtree_count--;
  DeleteNode(succ);
  return;
}

//-------------------------------
// SuccessoNode
// Obtaint the largest node
// next to current's value
//------------------------------

OrderedTreeNode*& OrderedTree::SuccessorNode(OrderedTreeNode *&node)
{
  if(node->left == NULL)
  {
    return node;
  } 
  else
  {
    return SuccessorNode(node->left);
  }

}

//--------------------------------------
// DeleteFromTree
// Delete node corressponding to the
// value from the tree
// Assume that value is always present
// in the tree - can implement a search
// function first if required
//--------------------------------------
void OrderedTree::DeleteFromTree(OrderedTreeNode *&node, int value)
{
  if(NULL == node)
  {
    return;
  }
  
  if(node->value == value)
  {
    // Current Node is the one to be deleted
    DeleteNode(node);

  }else if (value <= node->value)
  {
    node->subtree_count--;
    DeleteFromTree(node->left, value);
    
  }else
  {
    node->subtree_count--;
    DeleteFromTree(node->right, value);
  }
}

//-----------------------------
// FindNthNode
// Find the ith 
// element in the BST
//-----------------------------
OrderedTreeNode*& OrderedTree::FindNthNode(OrderedTreeNode *&node, int n)
{
  int size_left = 0;
  int size_right = 0;
  
  if(node->left != NULL){ 
    size_left  = node->left->subtree_count + 1 ;
  }

  if(node->right != NULL){
    size_right  = node->right->subtree_count + 1;
  }

  node->subtree_count--;
  
  if(n==size_left+1)
  {
    return node;
  } 
  else if(n < size_left+1)
  {
    return FindNthNode(node->left,n);
  }
  else 
  {
    return FindNthNode(node->right,n-size_left-1);
  }
}

//--------------------------
// DeleteNthSmallest
// Delete the Nth smallest
// and return it
//-------------------------

int OrderedTree::DeleteNthSmallest(int n)
{
  int current = -1;

  if(root == NULL)
  {
    throw EMPTY_TREE;
  }
  
  if(n>root->subtree_count+1)
  {
    throw OUT_OF_RANGE;
  }
 
  OrderedTreeNode *&node = FindNthNode(root, n);
  
  if(node != NULL)
  {
    current = node->value;
    DeleteNode(node);
  }
 
  return current;
}

//---------
// Test
//--------
int main(void)
{
  OrderedTree *tree;
  tree = new OrderedTree();
  cout << "created an empty tree\n";

  tree->InsertValue(7);
  tree->InsertValue(6);
  tree->InsertValue(5);
  tree->InsertValue(10);
  tree->InsertValue(12);
  tree->InsertValue(11);
  tree->PrintTree();

  cout << " Deleting 6th smallest\n";
  tree->DeleteNthSmallest(6);
  tree->PrintTree();

  cout <<"\n";
  tree->InsertValue(5);
  tree->InsertValue(26);
  tree->InsertValue(27);
  tree->InsertValue(10);
  tree->InsertValue(12);
  tree->InsertValue(11);
  
  cout<< " Deleting the 3rd smallest\n";
  tree->PrintTree();
  cout << "\n";
  tree->DeleteNthSmallest(3);
  tree->PrintTree();
}
