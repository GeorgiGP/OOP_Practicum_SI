// Task02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

const char* FILE_TO_WRITE_NAME = "result.dat";
const char* INPUT_FILE_NAME = "input.dat";
const int MAX_PAIRS_COUNT = 25;

struct Pair
{
	int firstNum;
	int secNum;
};

struct Relation
{
	Pair pairs[MAX_PAIRS_COUNT];
	int size;
};

void writeRelationToFile(Relation relation) {
	
	std::ofstream file(FILE_TO_WRITE_NAME, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	int pairSize = relation.size;
	
	for (int i = 0; i < pairSize; i++)
	{
		file.write(reinterpret_cast<char*>(&relation),pairSize);
	}
	file.close();
}
int getFileSize(std::ifstream& ifs) {
	
	if (!ifs.is_open())
	{
		return 0;
	}
	
	int currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();

	ifs.seekg(currentPos);
	return size;
}

void readRelationFromFile(Relation*& ptr, int& relationsCount, const char* filename) 
{
	
	std::ifstream ifs(filename, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) 
	{
		return;
	}

	int sizeOfFile = getFileSize(ifs);
	relationsCount = sizeOfFile / sizeof(Relation);
	ptr = new Relation[relationsCount];
	ifs.read((char*)ptr, sizeOfFile);

	ifs.close();
}

void addPairToRelation(Relation& relation, int first, int second) {
	
	if (relation.size >= MAX_PAIRS_COUNT) 
	{
		return;
	}

	relation.pairs[relation.size] = { first, second };
	relation.size++;
}

int main()
{
}

