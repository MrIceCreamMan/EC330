//My name is Zhuohao Yang, BU ID is U01579972
//when I want to add element to the hash table,
//I first hash the value with function h1 and then check if that space is occupied.
//If not then add it. But if so, I will still add it but take the old value out.
//Then I try to add the old value to the table.
//I repeat this process at most 26 times because there are maximun 26 spaces.
//If after 26 times, it is still not added, then I say it cannot be added

#include <iostream>
#include <vector>
#include <fstream>
#include "CuckooHashTable.h"

using namespace std;

CuckooHashTable::CuckooHashTable()
{
  vector<string> temp;
  for (int j=0; j<2; j++){
    contents.push_back(temp);
    for (int i=0; i<LOGICAL_SIZE; i++){
      contents[j].push_back("-");
    }
  }
  currentSize = 0;
}

int CuckooHashTable::hashCode(string value, int which)
{
  int num = atoi(value.c_str());
  int hashnum;
  if (which == 0){
    hashnum = num%13;
    return hashnum;
  }
  else if (which == 1){
    hashnum = 11-(num%11);
    return hashnum;
  }
  else{
    cout << "Wrong Table Number" << endl;
    return 0;
  }
}

void CuckooHashTable::add(string value)
{
  int which = currentSize%2;
  int where;
  string old;
  where = this->hashCode(value,which);
  if (contents[which][where] == "-"){
    contents[which][where] = value;
    currentSize = 0;
    return;
  }
  else{
    currentSize++; 
    if (currentSize == 1){
      contents[1][0] = value;
      contents[1][12] = "0";
    }
    if(value==contents[1][0] && currentSize>26 && contents[1][12]=="1"){
      cout << "------------------------------------------------------" << endl;
      cout << value << " cannot be added" << endl;
      cout << "------------------------------------------------------" << endl;
      currentSize = 0;
      return;
    }
    if(value==contents[1][0] && currentSize>26){
      contents[1][12] = "1";
    }
    old = contents[which][where];
    contents[which][where] = value;
    this->add(old);
  }
}

void CuckooHashTable::print()
{
  contents[1][0] = "-";
  contents[1][12] = "-";
  for (int i=0; i<2; i++){
    cout << "Table " << i+1 << ":" << endl;
    for (int j=0; j<LOGICAL_SIZE; j++){
      cout << contents[i][j] << endl;
    }
	cout << endl;
  }
return;
}
