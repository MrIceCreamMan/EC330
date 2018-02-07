#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int StringSearch(string filename, string pattern){
  const char* cFilename = filename.c_str();
  ifstream actualFile(cFilename);
  string fileCopy;
  string file;
  string individualWord;
  int count = 0;
  int totalwords = 0;
  int from = 0;
  int begin = 1;

  while (!actualFile.eof()){
    actualFile >> individualWord; 
    if (begin){
      fileCopy = individualWord;
      begin = 0;
    }
    else{
      file = fileCopy;
      fileCopy = fileCopy + " " + individualWord;
    }
    totalwords++;
  }
  actualFile.close();
  begin = 1;
  for (int i = 0; i < totalwords;i++){
    size_t found1 = file.find(pattern,from);
    if (found1 != std::string::npos){
      count++;
      from = found1+1;
    }
  }
  return count;
}

int main(int argc, char* argv[]){
  string filename, pattern;
  filename = argv[1];
  pattern = argv[2];
  int number;
  number = StringSearch(filename,pattern);
  cout << "There (is)are " << number << " \"" << pattern << "\"s in the file." << endl;
  return 0;
}
