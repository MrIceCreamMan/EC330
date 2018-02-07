// AUTHOR: Zachary Chapasko
// COLLABORATORS: None

/*
FULL OUTPUT:
Number of words that contain only letters: 26739138

Shortest pangram (size is 31) below:
trCypBrDmegQNsSlkzJ6xfoUHAQiV w

Number of words that do not contain {Zz}: 7278354
*/

/*
ANALYSIS:
Each function (fourA, fourB, fourC) is O(n) where n is the number of characters in BigData.txt.
Then it follows that the entire program is O(n) as well
Note: The multiplicative constant on fourB is very large (about 30-50+) so it takes significantly
	longer to run that problem than the rest.
*/


#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>

#define FIRST_LETTER "Zz"
#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALPHANUMERAL "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

using namespace std;

void fourA();
void fourB();
void fourC();

int main()
{
	fourA();
	fourB();
	fourC();
	return 0;
}

void fourA(){
	string word;
	int count = 0;
	size_t found;

	ifstream dataFeed("BigData.txt");
	while(dataFeed){
		// get word-by-word feed
		dataFeed >> word;

		// try to find non-alphabet character
		found = word.find_first_not_of(ALPHABET);

		// if a non-alphabet character is not present, increment count
		if(found == string::npos){
			count++;
		}
	}

	// close file, print count
	dataFeed.close();
	cout << "Number of words that contain only letters: " << count << endl;
	// Number of words that contain only letters: 26739138
}

void fourB(){
	char ch;
	vector<char> entireFile;

	// because vetor is so large we should carve out the space beforehand; do this with reserve
	entireFile.reserve(604501074);

	// open file, read in each char to the char vector
	ifstream dataFeed("BigData.txt");
	while(dataFeed >> noskipws >> ch){
		entireFile.push_back(ch);
	}
	dataFeed.close();

	// prepare map to map character to its most recent position in the entireFile vector
	unordered_map<char, int> charPosMap;
	charPosMap = {{'a',-1},{'b',-1},{'c',-1},{'d',-1},{'e',-1},{'f',-1},{'g',-1},{'h',-1},{'i',-1},{'j',-1},{'k',-1},{'l',-1},{'m',-1},{'n',-1},{'o',-1},{'p',-1},{'q',-1},{'r',-1},{'s',-1},{'t',-1},{'u',-1},{'v',-1},{'w',-1},{'x',-1},{'y',-1},{'z',-1}};

	vector<char> pangram;
	unordered_map<char, int>::iterator it, end;
	bool allChars;
	int ii, jj, len = entireFile.size(), pangramLen = entireFile.size();

	// IMPORTANT: psuedo head and tail pointers that contain our current range
	int max, min;

	// loop over every character in entireFile
	for(ii = 0; ii < len; ii++){
		// if we encounter an uppercase letter
		if(entireFile[ii] > 64 && entireFile[ii] < 91){
			// convert to equivalent lowercase character because this problem is not case-sensitive; update map value
			charPosMap[(char)(entireFile[ii] + 32)] = ii;
			// because we just got a valid character it is the maximum in our range; update accordingly
			max = ii;
			// set min to a value in the map; will update in the loop below
			min = charPosMap['a'];
			// say that we have encountered all characters; will set to false if that is not the case
			allChars = true;

			// iterate over map
			for(it = charPosMap.begin(), end = charPosMap.end(); it!= end; ++it){
				// if there is a smaller value in the map than the current min, update
				if(it->second < min){
					min = it->second;
				}
				// if value in map is -1 that means we haven't encountered that char yet, so we haven't encountered all chars
				if(it->second == -1){
					allChars = false;
				}
			}

			// if we have seen all the chars, we have a pangram
			if(allChars){
				// if pangram is smaller than the one we are currently storing, we have a new shortest pangram!
				if((max - min + 1) < pangramLen){
					// clear old pangram
					pangram.clear();
					// populate new pangram
					for(jj = min; jj <= max; jj++){
						pangram.push_back(entireFile[jj]);
					}
					// update pangram length
					pangramLen = pangram.size();
				}
			}

		// if we encounter a lowercase letter
		} else if (entireFile[ii] > 96 && entireFile[ii] < 123){
			charPosMap[entireFile[ii]] = ii;
			// because we just got a valid character it is the maximum in our range; update accordingly
			max = ii;
			// set min to a value in the map; will update in the loop below
			min = charPosMap['a'];
			// say that we have encountered all characters; will set to false if that is not the case
			allChars = true;

			// iterate over map
			for(it = charPosMap.begin(), end = charPosMap.end(); it!= end; ++it){
				// if there is a smaller value in the map than the current min, update
				if(it->second < min){
					min = it->second;
				}
				// if value in map is -1 that means we haven't encountered that char yet, so we haven't encountered all chars
				if(it->second == -1){
					allChars = false;
				}
			}

			// if we have seen all the chars, we have a pangram
			if(allChars){
				// if pangram is smaller than the one we are currently storing, we have a new shortest pangram!
				if((max - min + 1) < pangramLen){
					// clear old pangram
					pangram.clear();
					// populate new pangram
					for(jj = min; jj <= max; jj++){
						pangram.push_back(entireFile[jj]);
					}
					// update pangram length
					pangramLen = pangram.size();
				}
			}
		}
	}

	// print pangram
	pangramLen = pangram.size();
	cout << "\nShortest pangram (size is " << pangramLen << ") below:" << endl;
	for(ii = 0; ii < pangramLen; ii++){
		cout << pangram[ii];
	}
	cout << endl << endl;
	// Shortest pangram (size is 31) below:
	// trCypBrDmegQNsSlkzJ6xfoUHAQiV w
}

void fourC(){
	// first, read in dictionary.txt and copy it to a set
	string line;
	unordered_set<string> dictionary;
	ifstream dictionaryFile("dictionary.txt");
	if (dictionaryFile.is_open()){
		while (getline(dictionaryFile, line)){
			dictionary.insert(line);
		}
		dictionaryFile.close();
	}


	// now, read through BigData.txt
	string word, subWord;
	size_t punctuationPos;
	int count = 0;

	ifstream dataFeed("BigData.txt");
	while(dataFeed){
		// get word-by-word feed
		dataFeed >> word;

		// try to find punctuation (anything not 0-9, a-z, A-Z)
		punctuationPos = word.find_first_not_of(ALPHANUMERAL);

		while(punctuationPos != string::npos){
			// generate substring
			subWord = word.substr(0, punctuationPos);

			// if subWord does not contain first letter of first name, proceed to check dictionary
			if(subWord.find_first_of(FIRST_LETTER) == string::npos){

				// if subword belongs to dictionary, increment count
				if(dictionary.find(subWord) != dictionary.end())
					//cout << subWord << endl;
					count++;
			}

			// chop off the subWord from the start of the word string
			word = word.substr(punctuationPos + 1, word.length() - (punctuationPos + 1));

			// check for more punctuation
			punctuationPos = word.find_first_not_of(ALPHANUMERAL);
		}

		// check the rest of the word if it is not empty
		if(!word.empty()){
			if(word.find_first_of(FIRST_LETTER) == string::npos){
				if(dictionary.find(word) != dictionary.end()){
					count++;
				}
			}
		}
	}

	// close file and print number of words that don't contain first letter
	dataFeed.close();
	cout << "Number of words that do not contain {" << FIRST_LETTER << "}: " << count << endl;
	// Number of words that do not contain {Zz}: 7278354
}
