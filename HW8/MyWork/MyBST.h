//Zhuohao Yang U01579972
#ifndef MyBST_h
#define MyBST_h

#include <iostream>
#include "BST.h"
using namespace std;

class MyBST: public BST
{
 private:
  int totalnodes;

 public:
  MyBST();
  MyBST(int d);
  MyBST(vector<int>& nums);
  ~MyBST();

  vector<Rotation> transform(MyBST target);
  Node* rotateRight(Node* Q);
  Node* rotateLeft(Node* P);
  vector<int> findcoord(int key, Node* startP);
};

#endif
