#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void MergeFiles(string filename1, string filename2)
{
	ifstream file1(filename1);
	ifstream file2(filename2);
	ofstream output("output.txt");

	string nextWord1 = "", nextWord2 = "";
	char nextLetter1 = '?', nextLetter2 = '?';

	// Getting the first word of file 1
	file1.get(nextLetter1); // Get a letter
	while(isalpha(nextLetter1)) // Get the first word.
	{
		nextWord1 += nextLetter1;
		file1.get(nextLetter1);
	}

	// Getting the first word of file 2
	file2.get(nextLetter2); // Get a letter
	while(isalpha(nextLetter2)) // Get the first word.
	{
		nextWord2 += nextLetter2;
		file2.get(nextLetter2);
	}

	//////////// COMPARING WORDS ///////////////
	while (nextWord1 != "" | nextWord2 != "")
	{
		// First word is alphabetically earlier.
		if (nextWord1.compare(nextWord2) < 0 && nextWord1 != "")
		{
			output << nextWord1 << endl; // Write to file

			// Get the next word.
			nextWord1 = "";
			file1.get(nextLetter1);
			while(isalpha(nextLetter1) && !file1.eof())
			{
				nextWord1 += nextLetter1;
				file1.get(nextLetter1);
			}
		}
		else if (nextWord2 != "")// Second word is alphabetically earlier.
		{
			output << nextWord2 << endl; // Write to file

			// Get the next word.
			nextWord2 = "";
			file2.get(nextLetter2);
			while(isalpha(nextLetter2) && !file2.eof())
			{
				nextWord2 += nextLetter2;
				file2.get(nextLetter2);
			}
		}
	}

	file1.close();
	file2.close();
	output.close();
}

int main (int argc, char** argv)
{
	MergeFiles(argv[1], argv[2]);
	return 0;
}