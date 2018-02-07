// AUTHOR: Zachary Chapasko
// COLLABORATORS: None

/*
Algorithm is O(n^2 * log(n)) where n is the number of points provided. We have to generate every possible
line to make sure we don't miss any collinear points. To generate every line we have to match
the first point with each of the rest (so all of the rest is n - 1), the second point with each
of the points except the first and itself (so n - 2), and so on. We then have
(n - 1) + (n - 2) + (n - 3) + ... + 1, which is asymptotically equivalent to n^2. Then, we have to
insert the elements into a map/set, which is log(n). So we get a final runtime on the order of
O(n^2 * log(n))
*/

#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <set>
#include <map>

#define FILENAME "points.txt"

using namespace std;

void getNumPoints(int &numPoints){
	ifstream pointsFile(FILENAME);
	string line;

	if(pointsFile.is_open()){
		getline(pointsFile, line);	// only need first line so don't loop
		numPoints = stoi(line);		// get number of points from first line
		pointsFile.close();
	}
}

void getPoints(pair<double, double> *pPoints){
	// variables go here
	ifstream pointsFile (FILENAME);
	string line;
	bool first = true;
	int ii = 0;
	size_t space;

  	if (pointsFile.is_open()){
  		while (getline(pointsFile, line)){
  			if(first){
  				// we don't want to read the first line because we already have the number of points
  				first = false;
  			} else {
  				space = line.find(" ");
  				// .first corresponds to x; read from line start until space to get x
  				(*(pPoints + ii)).first = stod(line.substr(0, space++));
  				// .second corresponds to y; read from just after space until end of line to get y
  				(*(pPoints + ii)).second = stod(line.substr(space, line.length() - space));
  				// next slot in array
  				ii++;
  			}
  		}
  		pointsFile.close();
  	}
}

void getLines(pair<double, double> *pPoints, int numPoints, map<pair<double, double>,set<pair<double, double> > > &lines){
	// variables go here
	pair<double, double> key;
  	set<pair<double, double> > tempSet;
  	pair<pair<double, double>,set<pair<double, double> > > tempPair;
  	map<pair<double, double>,set<pair<double, double> > >::iterator it;
  	int ii, jj;

  	// nested for loop to compare all pairs of points (the nested loop is what makes this O(n^2))
  	for(ii = 0; ii < numPoints - 1; ii++){
  		for(jj = ii + 1; jj < numPoints; jj++){
  			// slope
  			key.first = ((pPoints + ii)->second - (pPoints + jj)->second)/((pPoints + ii)->first - (pPoints + jj)->first);

  			// intercept
  			key.second = (pPoints + ii)->second - (key.first * (pPoints + ii)->first);

  			// check if line is present in map
  			it = lines.find(key);

  			// if line is already in map, add points that are on that line
  			// else, insert new line in map with new points
  			if(it != lines.end()){
  				it->second.insert(*(pPoints + ii));
  				it->second.insert(*(pPoints + jj));
  			} else {
  				tempSet.clear();
  				tempSet.insert(*(pPoints + ii));
  				tempSet.insert(*(pPoints + jj));
  				tempPair.first = key;
  				tempPair.second = tempSet;
  				lines.insert(tempPair);
  			}
  		}
  	}
}


int main(){	
	// get number of points
	int numPoints;
	getNumPoints(numPoints);

	// now get the points
  	pair<double, double> points[numPoints];
  	pair<double, double> *pPoints = points;
  	getPoints(pPoints);

  	// key is a line represented as <slope, intercept>
  	// values are points represented as <x, y>
  	// let's get the lines!
  	map<pair<double, double>,set<pair<double, double> > > lines;
  	getLines(pPoints, numPoints, lines);

  	// variables for printing
  	map<pair<double, double>,set<pair<double, double> > >::iterator mapIt, mapEnd;
  	set<pair<double, double> > tempSet;
  	set<pair<double, double> >::iterator setIt, setEnd;
  	bool first = true;

  	// time to print
  	for(mapIt = lines.begin(), mapEnd = lines.end(); mapIt != mapEnd; ++mapIt){
  		tempSet = mapIt->second;

  		// if fewer than 4 colinear points then don't print
  		if(tempSet.size() < 4){
  			continue;
  		}

  		// if first line don't print separator
  		if(first){
  			first = false;
  		} else {
  			cout << endl;
  		}

  		// print points
  		for(setIt = tempSet.begin(), setEnd = tempSet.end(); setIt != setEnd; ++setIt){
  			cout << "(" << setIt->first << ", " << setIt->second << ")" << endl;
  		}
  	}

	return 0;
}
