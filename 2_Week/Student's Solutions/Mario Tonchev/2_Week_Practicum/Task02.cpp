#include <iostream>
#include <fstream>
using namespace std;

const int MAX_PAIRS = 25;

struct Pair {
	unsigned int a;
	unsigned int b;
};

struct Relation {
	Pair pairs[MAX_PAIRS];
	int size;
};

void WriteRelationToFile(const char* FILE_NAME, const Relation& relation) {
	ofstream ofStream(FILE_NAME);

	if (!ofStream.is_open())
	{
		return;
	}

	ofStream << relation.size << '\n';

	for (size_t i = 0; i < relation.size; i++)
	{
		ofStream << relation.pairs[i].a << " " << relation.pairs[i].b << '\n';
	}

	ofStream.close();
}

Relation* ReadRelationFromFile(const char* FILE_NAME) {
	Relation* relation = new Relation();

	ifstream ifStream(FILE_NAME);

	if (!ifStream.is_open())
	{
		return nullptr;
	}

	ifStream >> relation->size;
	ifStream.ignore(1, '\n');

	for (size_t i = 0; i < relation->size; i++)
	{
		ifStream >> relation->pairs[i].a;
		ifStream >> relation->pairs[i].b;
	}

	ifStream.close();

	return relation;
}

void WritePairToFile(const char* FILE_NAME, Pair pair) {
	ofstream ofStream(FILE_NAME, ios::app);
	ofStream << pair.a << " " << pair.b;
	ofStream.close();
}

void AddPairToRelation(const char* FILE_NAME, Relation& relation, Pair pair) {
	if (relation.size >= 25)
	{
		cout << "Relation has reached maximum capacity!";
		return;
	}

	relation.pairs[relation.size++] = pair;

	WritePairToFile(FILE_NAME, pair);
}

void PrintRelation(Relation& relation) {
	for (size_t i = 0; i < relation.size; i++)
	{
		cout << relation.pairs[i].a << " " << relation.pairs[i].b << endl;
	}
}

int main() {
	const char* FILE_NAME = "Relation.txt";
	Relation relation;

	relation.size = 10;

	for (size_t i = 0; i < 10; i++)
	{
		relation.pairs[i].a = i;
		relation.pairs[i].b = i + i;
	}

	WriteRelationToFile(FILE_NAME, relation);

	Relation* result = ReadRelationFromFile(FILE_NAME);
	PrintRelation(*result);

	AddPairToRelation(FILE_NAME, *result, { 5, 4 });
	cout << endl;
	PrintRelation(*result);

	delete result;
}