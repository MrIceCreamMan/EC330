#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void MergeFiles(string file1, string file2){
  const char* fname1 = file1.c_str();
  const char* fname2 = file2.c_str();
  ifstream inputfromfile;
  string words;
  int count1 = 0;
  int count2 = 0;
  
  inputfromfile.open(fname1);
  while (!inputfromfile.eof()){
    inputfromfile >> words;
    count1++;
  }
  count1--;
  inputfromfile.close();

  inputfromfile.open(fname2);
  while (!inputfromfile.eof()){
    inputfromfile >> words;
    count2++;
  }
  count2--;
  inputfromfile.close();

  string wordarray[count1+count2];
  inputfromfile.open(fname1);
  for (int i = 0; i < count1; i++){
    inputfromfile >> wordarray[i];
  }
  inputfromfile.close();

  inputfromfile.open(fname2);
  for (int j = 0; j < count2; j++){
    inputfromfile >> wordarray[j+count1];
  }
  inputfromfile.close();

  string temp;
  for (int k = 0; k < count1+count2; k++){
    for (int l = k+1; l < count1+count2; l++){
      if (wordarray[k] > wordarray[l]){
	temp = wordarray[k];
	wordarray[k] = wordarray[l];
	wordarray[l] = temp;
      }
    }
  }
  for (int k = 0; k < count1+count2; k++){
    cout << wordarray[k] << endl;
  }
  
  return;
}

int main(int argc, char* argv[]){
  string file1, file2;
  file1 = argv[1];
  file2 = argv[2];
  MergeFiles(file1,file2);
  return 0;
}
