//AUTHOR: Zachary Chapasko
//COLLABORATORS: None
#ifndef MYBST_h
#define MYBST_h

#include "BST.h"

using namespace std;

class MyBST: public BST{
public:
	MyBST(vector<int>& nums) : BST(nums) {}
	vector<Rotation> transform(MyBST target);
	Node* rotateRight(Node* Q);
	Node* rotateLeft(Node* P);
	void search(int key, Node * node);
	void transform(Node *head, Node *targetHead, Node* parent, RotationType childSide);

private:
	vector<Rotation> rotations;
	vector<RotationType> zigZags;
	MyBST(){}	
};

#endif /* MYBST_h */
