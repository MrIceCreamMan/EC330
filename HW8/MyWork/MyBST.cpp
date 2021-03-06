//Zhuohao Yang U01579972

#include "MyBST.h"

/**
 * Computes how to transform this MyBST into the target MyBST using rotations.
 * Returns a vector of rotations indicating which rotations around which nodes
 *  must be performed to transform this into the target.
 *
 * IMPORTANT: We want to transform T1 into T2 so the call should look like
 * rotations = t1.transform(t2)
 */

using namespace std;

MyBST::MyBST():BST()
{
  totalnodes=0;
}

MyBST::MyBST(int num):BST(num)
{
  totalnodes=1;
}

MyBST::MyBST(vector<int>& nums):BST(nums)
{
  totalnodes=nums.size();
}

MyBST::~MyBST()
{
}

vector<int> MyBST::findcoord(int key, Node* startP){
  int count2 = 0;
  int index = 0;
  vector<int> result;
  vector<vector<Node*> > find;
  int depth2 = 0;
  vector<Node*> layer02;
  find.push_back(layer02);
  find[0].push_back(startP);
  while (count2 != totalnodes){
    vector<Node*> layern2;
    find.push_back(layern2);   
    for (int i=0; i<find[depth2].size(); i++){
      if (find[depth2][i]!=nullptr){
	if (find[depth2][i]->key == key){
	  count2 = totalnodes;
	  index = i;
	  break;
	}
	if (find[depth2][i]->left != nullptr){
	  find[depth2+1].push_back(find[depth2][i]->left);
	  count2++;
	}
	else{
	  find[depth2+1].push_back(nullptr);
	}
	if (find[depth2][i]->right != nullptr){
	  find[depth2+1].push_back(find[depth2][i]->right);
	  count2++;
	}
	else{
	  find[depth2+1].push_back(nullptr);
	}
      }//nullptr
      else{
	find[depth2+1].push_back(nullptr);
	find[depth2+1].push_back(nullptr);
      }
    }
    depth2++;
  }
  result.push_back(depth2);
  result.push_back(index);
  return result;
}

vector<Rotation> MyBST::transform(MyBST target) {

  /*** This is what you have to do ***/
  int count = 1;
  vector<vector<Node*> > goal;
  int depth=0;
  vector<Node*> layer0;
  goal.push_back(layer0);
  goal[depth].push_back(target.root);
  while (count < totalnodes){
    vector<Node*> layern;
    goal.push_back(layern);
    for (int i=0; i<goal[depth].size(); i++){
      if (goal[depth][i]!=nullptr){
	if (goal[depth][i]->left != nullptr){
	  goal[depth+1].push_back(goal[depth][i]->left);
	  count++;
	}
	else{
	  goal[depth+1].push_back(nullptr);
	}
	if (goal[depth][i]->right != nullptr){
	  goal[depth+1].push_back(goal[depth][i]->right);
	  count++;
	}
	else{
	  goal[depth+1].push_back(nullptr);
	}
      }
      else{
	goal[depth+1].push_back(nullptr);
	goal[depth+1].push_back(nullptr);
      }
    }
    depth++;
  }
  /*
    for (int i=0; i<depth+1; i++){
    cout << goal[i].size() << "ddd";
    for (int j=0; j<goal[i].size(); j++){
    if (goal[i][j]!=nullptr)
    cout << goal[i][j]->key << " ";
    else
    cout << "_ ";
    }
    cout << endl;
    }
  */
  vector<Rotation> mylist;
  RotationType myRot;
  int done = 0;
  depth = 0;
  Node *previous_node,*current_node,*cnode2;
  Node *root2 = root;
  int lr;
  vector<Node*> processNodes;
  vector<RotationType> processRot;
  vector<int> coord;

  while(done != totalnodes){
    for (int c=0; c<goal[depth].size(); c++){
      if (goal[depth][c]!=nullptr){
	//cout <<c << "target " << goal[depth][c]->key << "-----";
	current_node = root2;
	previous_node = current_node;
	//find the location of the target node in target tree
	int power1 = depth; int index1 = c; int cmp = 1;
	if (power1>0){
	  for (int k=0; k<power1-1; k++){
	    cmp = cmp*2;
	  }
	}
	for (int e=0; e<power1; e++){
	  if (index1<cmp){
	    previous_node = current_node;
	    lr = 0;
	    current_node=current_node->left;
	  }
	  else{
	    previous_node = current_node;
	    lr = 1;
	    current_node=current_node->right;
	    index1 = index1 - cmp;
	  }
	  cmp = cmp/2;
	}
	//cout << "curr " << current_node->key << " prev " << previous_node->key << endl;
	//find the location of the target node in current tree
	coord = findcoord(goal[depth][c]->key,current_node);
	cnode2 = current_node;
	int power = coord[0]; int index = coord[1]; int compare = 1;
	if (power == 1){
	  done++;
	  //c<goal[depth].size();
	  // cout << "break" << endl;
	  //break;
	}
	else{
	  for (int p=0; p<power-2; p++){
	    compare = compare*2;
	  }
	  for (int i=0; i<power-1; i++){
	    if (index<compare){
	      processNodes.push_back(cnode2);
	      myRot = ZIG;
	      //cout << "Zig on " << cnode2->key << endl;
	      processRot.push_back(myRot);
	      cnode2=cnode2->left;
	    }
	    else{
	      processNodes.push_back(cnode2);
	      myRot = ZAG;
	      // cout << "Zag on " << cnode2->key << endl;
	      processRot.push_back(myRot);
	      cnode2=cnode2->right;
	      index = index-compare;
	    }
	    compare = compare/2;
	  }
	  RotationType ro1,ro2;
	  ro1 = ZIG;
	  ro2 = ZAG;

	  while (processNodes.size()>1){
	    Rotation* rot = new Rotation(processNodes.back()->key,processRot.back());
	    mylist.push_back(*rot);
	    if (processRot.back() == ro1){
	      if (processRot[processRot.size()-2]==ro1)
		processNodes[processNodes.size()-2]->left = rotateRight(processNodes.back());
	      else
		processNodes[processNodes.size()-2]->right = rotateRight(processNodes.back());
	    }
	    else if (processRot.back() == ro2){
	      if (processRot[processRot.size()-2]==ro1)
		processNodes[processNodes.size()-2]->left = rotateLeft(processNodes.back());
	      else
		processNodes[processNodes.size()-2]->right = rotateLeft(processNodes.back());
	    }
	    else
	      cout << "Things Wrong in while loop" << endl;
	    processNodes.pop_back();
	    processRot.pop_back();
	  }
	  Rotation* rot  = new Rotation(processNodes.back()->key,processRot.back());
	  mylist.push_back(*rot);
	  if (processRot[0]==ro1){
	    current_node = rotateRight(processNodes.back());
	  }
	  else{
	    current_node = rotateLeft(processNodes.back());
	  }
	  processNodes.pop_back();
	  processRot.pop_back();

	  if(depth==0 && c==0){
	    root2 = current_node;
	  }
	  else{
	    if (lr == 0){
	      previous_node->left=current_node;
	    }
	    else{
	      previous_node->right=current_node;
	    }
	  }
	  done++;
	}
      }
    }
    depth++;
  }
  return mylist;    	
}

Node* MyBST::rotateRight(Node* Q)
{
    Node* P = Q->left;
    Q->left = P->right;
    P->right = Q;
    return P;
}

Node* MyBST::rotateLeft(Node* P)
{
    Node* Q = P->right;
    P->right = Q->left;
    Q->left = P;
    return Q;
}
