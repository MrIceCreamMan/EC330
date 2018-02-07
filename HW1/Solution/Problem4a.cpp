#include <iostream>
#include <string>
#include <fstream>

// This is only one way of solving the problem. If you had a different method that worked, go you :)

using namespace std;

int StringSearch(string filename, string pattern)
{
	fstream file(filename);
	string content;
	char next_letter = '?';

	// Reading the entire file until there is nothing to read. 
	// ( I read it character by character, but the method is entirely your choice.
	//   It's even your choice if you want to do this step. )
	while (!file.eof())
	{
		file.get(next_letter);
		content += next_letter;
	}
	file.close();

	// Comparing substrings, whose length is same as pattern, with pattern.
	// Comparing them from position 0 ~ patternlength
	//								1 ~ patternlength+1
	//								2 ~ patternlength+2 etc...
	int occurences = 0;
	for (int i=0; i<(content.size() - pattern.size()); i++)
		if (content.substr(i, pattern.size()).compare(pattern) == 0)
			occurences++;

	return occurences;
}

int main (int argc, char** argv)
{
	cout << StringSearch(argv[1], argv[2]) << endl; // Call the function.
	return 0;
}