//AUTHOR: Zachary Chapasko
//COLLABORATORS: None
#include "BST.h"
#include "MyBST.h"
#include <fstream>

using namespace std;

int main(){
	vector<int> one, two;
	string line;

	// load first tree into vector representation
	one.clear();
  	ifstream first("T1.txt");
  	if(first.is_open()){
    	while(getline(first,line)){
      		one.push_back(stoi(line));
    	}
    	first.close();
  	}

  	// load second tree into vector representation
  	two.clear();
  	ifstream second("T2.txt");
  	if(second.is_open()){
    	while(getline(second,line)){
      		two.push_back(stoi(line));
    	}
    	second.close();
  	}

  	// create BST representation using derived class of provided class
  	MyBST t1(one);
  	MyBST t2(two);

  	// do the transform and capture the required rotations
  	vector<Rotation> rotations = t1.transform(t2);

  	// print the rotations
  	vector<Rotation>::iterator it, end;
  	for(it = rotations.begin(), end = rotations.end(); it != end; ++it){
  		cout << it->print() << endl;
  	}

	return 0;
}
