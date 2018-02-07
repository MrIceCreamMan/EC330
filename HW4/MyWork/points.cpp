//My name is Zhuohao Yang, BU ID is U01579972

//My program's run time is theta of n^3 because there are three loops
//The outer loop go through each point of the input - n repetitions
//The middle loop calculates the y-intercept and slope and then
//go through the entire list - (n-1) repetitions
//The inner loop checks if the rest of points are on the line with
//the y-intercept and the slope calculated in middle loop - (n-2) repetitions
//total runtime = n * 1/2 * (n-1) * 1/2 * (n-2) = theta of (n^3)

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){
  ifstream myinput;
  float x,y;
  vector<float> myvecx,myvecy;
  myinput.open("points.txt");
  int count_pt;
  myinput >> count_pt;
  for (int i=0; i < count_pt; i++){
    myinput >> x;
    myvecx.push_back(x);
    myinput >> y;
    myvecy.push_back(y);
  }
  myinput.close();
  float x1,x2,x3,y1,y2,y3;
  float slope,y_int;
  int how_many = 2;
  vector<float> tobecheckedx,tobecheckedy;
  vector<float> slopevec,yintvec;
  int print_num = 0;
  bool ifprint;
  for (int i=0; i < count_pt; i++){
    x1 = myvecx[i];
    y1 = myvecy[i];
    for (int j=i+1; j < count_pt; j++){
      x2 = myvecx[j];
      y2 = myvecy[j];
      slope = (y2-y1)/(x2-x1);
      y_int = y1-x1*slope;
      for (int k=j+1; k < count_pt; k++){
	x3 = myvecx[k];
	y3 = myvecy[k];
	if(x3*slope+y_int == y3){
	  how_many++;
	  tobecheckedx.push_back(x3);
	  tobecheckedy.push_back(y3);
	}
      }

      //add p1 and p2 to the list of points if there are 4 or more
      if (how_many >= 4){
	tobecheckedx.push_back(x1);
	tobecheckedx.push_back(x2);
	tobecheckedy.push_back(y1);
	tobecheckedy.push_back(y2);
	ifprint = true;
	//check if it's already printed
      	for (int w = 0; w<print_num; w++){
       	  if (slope == slopevec[w] && y_int == yintvec[w])
	    ifprint = false;
       	}
	//print out the list of colinear points and also 
	if (ifprint){
	  cout << endl;
	  for (int f=0; f < how_many; f++){
	    cout << "(" << tobecheckedx[f] << "," << tobecheckedy[f] << ")" << endl;
	  }
	  slopevec.push_back(slope);
	  yintvec.push_back(y_int);
	  print_num++;
	}

      }//bracket for if how many > 4

      //clear the list and reset 'how_many'
      tobecheckedx.clear();
      tobecheckedy.clear();
      how_many=2;

    }//bracket for j loop
  }
  //print vertical line
  float xint;
  int hmany=1;
  bool iprint= true;
  int printn=0;
  vector<float> tbcx,tbcy;
  vector<float> xintvec;
  for (int r = 0; r< count_pt; r++){
    for (int c = r; c < count_pt; c++){
      if (myvecx[r]==myvecx[c]){
	tbcx.push_back(myvecx[c]);
	tbcy.push_back(myvecy[c]);
	hmany++;
      }
    }
    if (hmany>=4){
      iprint = true;
      tbcx.push_back(myvecx[r]);
      tbcy.push_back(myvecy[r]);
      for (int u = 0; u<printn; u++){
	if (xint == xintvec[u])
	  iprint = false;
      }
      //print out the line
      if (iprint){
	cout << endl;
	for (int g=0; g < hmany; g++){
	  cout << "(" << tbcx[g] << "," << tbcy[g] << ")" << endl;
	}
	xintvec.push_back(xint);
	printn++;
      }	
    }
    xintvec.clear();
    hmany=1;
  }

  return 0;
}
