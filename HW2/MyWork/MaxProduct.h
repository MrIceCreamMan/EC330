#ifndef _HW2_MaxProduct
#define _HW2_MaxProduct

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class MaxProductClass
{
private:
  long array[100];
  ifstream actualFile;
public:
  MaxProductClass();
  ~MaxProductClass();
	
  long MaxProduct(const char* filename);
  void ShowArray(int num);
};

#endif
