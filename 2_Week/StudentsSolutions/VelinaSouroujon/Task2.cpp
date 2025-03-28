#include <iostream>
#include <fstream>
using namespace std;

const int MAX_PAIRS = 25;

struct Pair
{
	int x;
	int y;
};

struct Relation
{
	int length;
	Pair pairs[MAX_PAIRS];
};

Pair readPairFromFile(ifstream& inFile)
{
	Pair pair = {};
	if (!inFile.is_open())
	{
		cerr << "File is not open!" << endl;
		return pair;
	}

	inFile >> pair.x >> pair.y;

	return pair;
}

bool writePairToFile(const Pair& pair, ofstream& outFile)
{
	if (!outFile.is_open())
	{
		return false;
	}

	outFile << pair.x << ' ' << pair.y << '\n';

	return true;
}

bool writeRelationToFile(const Relation& relation, ofstream& outFile)
{
	if (!outFile.is_open())
	{
		return false;
	}

	for (size_t i = 0; i < relation.length; i++)
	{
		Pair pair = relation.pairs[i];

		if (!writePairToFile(pair, outFile))
		{
			return false;
		}
	}

	return true;
}

bool addPairToRelation(const Pair& pair, Relation& relation)
{
	if (relation.length >= MAX_PAIRS)
	{
		return false;
	}

	relation.pairs[relation.length] = pair;
	relation.length++;

	return true;
}

Relation readRelationFromFile(ifstream& inFile)
{
	Relation relation = {};

	if (!inFile.is_open())
	{
		return relation;
	}

	while (inFile.peek() != EOF)
	{
		Pair pair = readPairFromFile(inFile);

		if (!addPairToRelation(pair, relation))
		{
			cerr << "Too many pairs!";
			return relation;
		}
	}

	return relation;
}

int main()
{
	ifstream inFile("input.txt");
	Relation relation = readRelationFromFile(inFile);
	inFile.close();

	addPairToRelation({ 1, 2 }, relation);
	addPairToRelation({ 3, 4 }, relation);
	addPairToRelation({ 5, 6 }, relation);
	addPairToRelation({ 7, 8 }, relation);
	addPairToRelation({ 9, 10 }, relation);

	ofstream outFile("output.txt");
	writeRelationToFile(relation, outFile);
	outFile.close();

	return 0;
}
