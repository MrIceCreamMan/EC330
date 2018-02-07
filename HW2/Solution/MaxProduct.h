// AUTHOR: Zachary Chapasko
// COLLABORATORS: None
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class MaxProductClass {
public:
	MaxProductClass();
	~MaxProductClass();
	long MaxProduct(string fileName);

private:
	vector<long> tempLine;
	vector<long> maxes;
};
