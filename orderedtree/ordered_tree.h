//-----------------------------------------------------------------------------
// File: ordered_tree.h
// Purpose: Implementation of an ordered tree which support deletes by ordered statistic
// Example: Delete the Nth smallest and return 
// Author: Baddn
//------------------------------------------------------------------------------

#include <iostream>
using namespace std;

#define VALUE_EMTPY 1;
#define NULL_NODE 2;
#define OUT_OF_RANGE 3;
#define EMPTY_TREE 4;

struct OrderedTreeNode
{
  int value;
  int subtree_count;
  OrderedTreeNode * left;
  OrderedTreeNode * right;
};

class OrderedTree
{

 private:
  struct OrderedTreeNode *root;
  
 public:
  OrderedTree();
  ~OrderedTree();
  bool IsEmptyTree();
  void InsertValue(int value);
  void DeleteByValue(int value);
  int DeleteNthSmallest(int n);
  void PrintTree();

 private:
  void InsertIntoTree(OrderedTreeNode *&node, int value);
  void DeleteFromTree(OrderedTreeNode *&node, int value);
  void DeleteNode(OrderedTreeNode *&node);
  void PrintNodes(OrderedTreeNode *node);
  OrderedTreeNode*& SuccessorNode(OrderedTreeNode *&node);
  OrderedTreeNode*& FindNthNode(OrderedTreeNode *&node, int n);
};
  
