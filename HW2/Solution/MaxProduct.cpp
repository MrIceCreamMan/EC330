// AUTHOR: Zachary Chapasko
// COLLABORATORS: None
#include "MaxProduct.h"

MaxProductClass::MaxProductClass(){}

MaxProductClass::~MaxProductClass(){}

// Time complexity: Order n where n is equal to the total number of numbers in the file
// Space complexity: Constant
long MaxProductClass::MaxProduct(string fileName){
	// variables go here
	string line, num;
	size_t start = 0, finish = 0;
	int ii, jj, kk, len;
	long singleMax, doubleMax, tripleMax, doubleTemp, trueMax;
	vector<long>::iterator it;
	vector<long>::iterator end;
	ifstream myfile (fileName);

	// everything else goes here
  	if (myfile.is_open()){
  		// get line
    	while (getline(myfile, line)){
    		// repeat "forever"
    		while(true){
    			// find next space in string
    			finish = line.find(' ', start);
    			// stop repeating immediately if no spaces are left
    			if(finish == string::npos){
    				break;
    			}
    			// get number
    			num = line.substr(start, finish - start);
    			// set start ahead of finish to grab next space
    			start = finish + 1;
    			// add to vector for processing
    			tempLine.push_back((long)stoi(num));
    		}
    		// reset string positions
    		start = 0;
    		finish = 0;

    		// do processing

    		len = tempLine.size();

    		// if length is whacky
    		if(len < 1){
    			cout << "ERROR" << endl;
    			break;
    		}

    		// do small vector cases
    		if(len == 1){
    			maxes.push_back(tempLine[0]);
    			tempLine.clear();
    		} else if (len == 2){
    			maxes.push_back(max(max(tempLine[0], tempLine[1]), tempLine[0] * tempLine[1]));
    			tempLine.clear();
    		} else {
    			// do large vector case

    			// preserve single largest element
    			singleMax = max(tempLine[0], tempLine[1]);

    			// preserve product of two elements
    			doubleMax = tempLine[0] * tempLine[1];

    			// preserve product of three elements
    			tripleMax = doubleMax * tempLine[2];

    			// loop it!
    			for(ii = 0, jj = 1, kk = 2; kk < len; ii++, jj++, kk++){
    				// update largest single element
    				singleMax = max(singleMax, tempLine[kk]);

    				// update largest "double" element
    				doubleTemp = tempLine[jj] * tempLine[kk];
    				doubleMax = max(doubleMax, doubleTemp);

    				//update largest "triple" element
    				tripleMax = max(tripleMax, tempLine[ii] * doubleTemp);
    			}

    			// find local maximum
    			maxes.push_back(max(max(singleMax, doubleMax), tripleMax));
    			tempLine.clear();
    		}    		
    	}
    	myfile.close();
  	}

  	// set up printing and global maximum search
  	trueMax = maxes[0];
    it = maxes.begin();
    end = maxes.end();
    for(; it != end; ++it){
    	trueMax = max(trueMax, *it);
    	cout << *it << endl;
    }

    return trueMax;
}
