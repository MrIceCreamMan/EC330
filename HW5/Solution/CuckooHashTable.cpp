//
//  CuckooHashTable.h
//  CuckooHashTable
//
#include "CuckooHashTable.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

CuckooHashTable::CuckooHashTable()
{
//  Initialize hastable
	for (int i=0; i<2; i++)
	{
		vector<string> new_table;
		for (int j=0; j<LOGICAL_SIZE; j++)
			new_table.push_back("-");
		contents.push_back(new_table);
	}
	currentSize = 0;
}

int CuckooHashTable::hashCode(string value, int which)
{
//  Compute hash function for input 'value', table 'which'
	if (which == 1)
		return atoi(value.c_str()) % 13;
	else if (which == 2)
		return 11 - (atoi(value.c_str()) % 11);
	else 
		return LOGICAL_SIZE;
}

void CuckooHashTable::add(string value)
{
//  Insert 'value' to hash table
	int hash_type = 1;
	int index = hashCode(value, hash_type);

	string start_value = value;
	int    start_index = index;
	int    start_hasht = hash_type;
	do {
		value.swap(contents[hash_type-1][index]);
		hash_type = 3 - hash_type;
		index = hashCode(value, hash_type);
		
		if (value == start_value &&
			index == start_index && 
			hash_type == start_hasht){
			cout << "ERROR: Inserting " + value + " causes an infinite loop.\n";
			return;
		}
	}
	while (value != "-");
	this->currentSize++;
}

void CuckooHashTable::print()
{
//  Print the contents of the table.
	for (int i=0; i<2; i++)
	{
		cout << "Table " << i+1 << endl;
		for (int j=0; j<LOGICAL_SIZE; j++)
			cout << contents[i][j] << endl;
		cout << endl;
	}
}