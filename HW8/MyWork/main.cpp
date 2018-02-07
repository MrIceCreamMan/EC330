//Zhuohao Yang U01579972
#include <iostream>
#include <fstream>
#include "BST.h"
#include "MyBST.h"
using namespace std;

int main(){
  int n;
  ifstream file1("T1.txt");
  vector<int> nums1;
  while (file1>>n)
    nums1.push_back(n);
  file1.close();
  MyBST tree1(nums1);

  ifstream file2("T2.txt");
  vector<int> nums2;
  while (file2>>n)
    nums2.push_back(n);
  file2.close();
  MyBST tree2(nums2);
  vector<Rotation> result = tree1.transform(tree2);
  for (int i=0; i<result.size(); i++){
    cout << result[i].print() << endl;
  }

  return 0;
}
