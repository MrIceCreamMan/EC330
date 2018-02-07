//Zhuohao Yang U01579972
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Node
{
private:
  char key; 
  int cnum;
  bool leaf;
  vector<Node*> children;
public:
  Node(){
    key = '*';
    cnum = 0;
    leaf = false;
  };
  Node(char letter){
    key = letter;
    cnum = 0;
    leaf = false;
  };
  void add(string word){
    for (int i=0; i<cnum; i++){
      if (word[0]==children[i]->key){
	if (word.length()==1){
	  children[i]->leaf=true;
	}
	else{
	  string newword = word;
	  newword.erase(newword.begin());
	  children[i]->add(newword);
	}
	return;
      }
    }
    Node* newnode = new Node(word[0]);
    children.push_back(newnode);
    cnum++;
    if (word.length()==1){
      children[cnum-1]->leaf=true;
    }
    else{
      string newword = word;
      newword.erase(newword.begin());
      children[cnum-1]->add(newword);
    }
    return;
  };
  bool check(string word){
    for (int i=0; i<cnum; i++){
      if (word[0]==children[i]->key){
	if (word.length()==1){
	  if (children[i]->leaf)
	    return true;
	  else
	    return false;
	}
	else{
	  string newword = word;
	  newword.erase(newword.begin());
	  return children[i]->check(newword);
	}
      }
    }
    return false;
  };
};

int fourA(string dataname){
  const char* cData = dataname.c_str();
  string word;
  int count = 0;
  int letters = 1;
  ifstream myData(cData);
  while (myData >> word){
    for (int i=0; i<word.length(); i++){
      if ((word[i]<='z' && word[i]>='a')||(word[i]<='Z' && word[i]>='A')){
      }
      else{
	letters = 0;
	break;
      }
    }
    if (letters == 1){
      count++;
    }
    letters = 1;
  }
  myData.close();
  return count;
}

string fourB(string dataname){
  const char* cData = dataname.c_str();
  string sentence = "";
  string result;
  char letter;
  int count = 0;
  int first = 1;
  int min,full;
  int array[26];
  for (int i=0; i<26; i++){
    array[i] = 0;
  }
  ifstream myData(cData);
  while (myData >> noskipws >> letter){
    count++;
    sentence = sentence+letter;
    if (letter<='z' && letter>='a'){
      array[letter-'a']++;
    }
    else if(letter<='Z' && letter>='A'){
      array[letter-'A']++;
    }
    full = 1;
    for (int j=0;j<26;j++)
      full=array[j]*full;
    if ((full!=0)&&(first==1)){
      min = count;
      result = sentence;
      first = 0;
    }
    while (full!=0){
      if (sentence[0]<='z' && sentence[0]>='a'){
	array[sentence[0]-'a']--;
	if (array[sentence[0]-'a']==0){
	  array[sentence[0]-'a']++;
	  full = 0;
	}
	else{
	  sentence.erase(sentence.begin());
	  count--;
	}
      }
      else if (sentence[0]<='Z' && sentence[0]>='A'){
	array[sentence[0]-'A']--;
	if (array[sentence[0]-'A']==0){
	  array[sentence[0]-'A']++;
	  full = 0;
	}
	else{
	  sentence.erase(sentence.begin());
	  count--;
	}
      }
      else{
	sentence.erase(sentence.begin());
	count--;
      }
    }
    if ((count < min)&&(first==0)){
      result = sentence;
      min = count;
    }
  }

  myData.close();
  return result;
}

int fourC(string dataname, string dic){
  const char* cData = dataname.c_str();
  const char* cDict = dic.c_str();
  string word;
  int count=0;
  int valid;
  Node nroot;
 
  ifstream myDict(cDict);
  while (myDict >> word){
    nroot.add(word);
  }
  myDict.close();

  ifstream myData(cData);
  while (myData >> word){
    valid = 1;
    for (int i=0; i<word.length(); i++){
      if (word[i]=='z' || word[i]=='Z'){
	valid = 0;
      }
    }
    if (nroot.check(word)&&valid==1){
      count++;
    }
  }
  myData.close();

  return count;
}

int main(int argc, char* argv[]){
  string dataname, dic;
  dataname = "BigData.txt";
  dic = "dictionary.txt";
  int number;
  string pangram;
  cout << "=======================================================================" << endl;
  number = fourA(dataname);
  cout << "Problem 4A:\n    There are " << number << " \"words\" that contain only letters" << endl;
  cout << "-----------------------------------------------------------------------" << endl;
  pangram = fourB(dataname);
  int l = pangram.length();
  cout << "Problem 4B:\n    The shortest pangram is:\n    \"" << pangram << "\" with length = " << l << endl;
  cout << "-----------------------------------------------------------------------" << endl;
  number = fourC(dataname,dic);
  cout << "Problem 4C:\n    There are " << number  << " dictionary words without \"Z\" or \"z\" in the file." << endl;
  cout << "=======================================================================" << endl;
  return 0;
}
