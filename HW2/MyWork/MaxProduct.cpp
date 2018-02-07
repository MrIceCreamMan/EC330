//My name is Zhuohao Yang,
//My BU ID is U01579972


#include "MaxProduct.h"
#include <iostream>
using namespace std;


MaxProductClass::MaxProductClass()
{
}

MaxProductClass::~MaxProductClass()
{
  // cout << "MaxProductClass destructed." << endl;
}

long MaxProductClass::MaxProduct(const char* filename)
{
  actualFile.open(filename);
  int i = 0;
  int length_seq = 0;
  int set_local = 1;
  int set_global = 1;
  long number;
  long local_max;
  long global_max;
  long product;

  while(actualFile >> number){
    
    if (set_local == 1){
      local_max = number;
      if (set_global == 1){
	global_max = number;
	set_global = 0;
      }
      set_local = 0;
    }

    while (number!=-999999){                        //n times
      array[i] = number;                            //read one seqence into the array
      actualFile >> number;
      i++;
    }
    length_seq = i;
    for (int j=0; j<length_seq-2; j++){             //n-2 times
      product = array[j]*array[j+1]*array[j+2];     //check for three multiply together
      if (product > local_max)
	local_max = product;
    }
    for (int j=0; j<length_seq-1; j++){             //n-1 times
      product = array[j]*array[j+1];                //check for two multiply together
      if (product > local_max)
	local_max = product;
    }
    for (int j=0; j<length_seq; j++){               //n times
      product = array[j];                           //check for individual element
      if (product > local_max)
	local_max = product;
    }
    if (local_max>global_max)                       //update global maximum
      global_max = local_max;
    cout << local_max << endl;
    i = 0;
    set_local = 1;                                  //reset maximum for each sequence
  }
  return global_max;
}

void MaxProductClass::ShowArray(int num)            //debug purpose function, trivial
{
  for (int i = 0; i < num; i++)
    cout << array[i] << " ";
  cout << endl;
}
