#include <iostream>
#include <fstream>
using namespace std;

const int MAX_LINE_LENGTH = 256;
const int MAX_WORD_LENGTH = 64;

const char OPENING_BRACKET = '{';
const char CLOSING_BRACKET = '}';

const char KEY_VALUE_PAIRS_FILE[] = "input.txt";
const char TEXT_FILE[] = "text.txt";
const char COPY_FILE[] = "copy.txt";

struct KeyValuePair
{
	char key[MAX_WORD_LENGTH];
	char value[MAX_WORD_LENGTH];
};

struct Dictionary
{
	KeyValuePair* pairs;
    int count;
};

void resetString(char* str, char defaultValue)
{
	if (str == nullptr)
	{
		return;
	}

	for (size_t i = 0; str[i] != '\0'; i++)
	{
		str[i] = defaultValue;
	}
}

int getLinesCount(ifstream& inFile)
{
	if (!inFile.is_open())
	{
		return -1;
	}

	char line[MAX_LINE_LENGTH];
	int linesCount = 0;

	while (inFile.getline(line, MAX_LINE_LENGTH))
	{
		linesCount++;
	}

	inFile.clear();
	inFile.seekg(0, ios::beg);

	return linesCount;
}

Dictionary readKeyValuePairs(ifstream& inFile)
{
	Dictionary dic = {};
	if (!inFile.is_open())
	{
		cerr << "File not opened\n";
		return dic;
	}

	int count = getLinesCount(inFile);

	if (count < 0)
	{
		cerr << "Error reading file\n";
		return dic;
	}

	dic.count = count;
	dic.pairs = new KeyValuePair[dic.count];
	int idx = 0;

	while (idx < dic.count && (inFile.peek() != EOF))
	{
		KeyValuePair* kvp = dic.pairs;
		inFile >> kvp[idx].key;
		inFile.ignore();
		inFile.getline(kvp[idx].value, MAX_WORD_LENGTH);
		idx++;
	}

	return dic;
}

char* getValue(const char* key, const Dictionary& dic)
{
	if (dic.pairs == nullptr || key == nullptr)
	{
		return nullptr;
	}

	for (size_t i = 0; i < dic.count; i++)
	{
		KeyValuePair& kvp = dic.pairs[i];

		if (strcmp(key, kvp.key) == 0)
		{
			return kvp.value;
		}
	}

	return nullptr;
}

bool getText(const Dictionary& dic, ifstream& inFile, const char* copyFilePath)
{
	if (dic.pairs == nullptr || copyFilePath == nullptr)
	{
		return false;
	}
	if (!inFile.is_open())
	{
		return false;
	}

	ofstream copy(copyFilePath);
	bool isInsideOpeningBracket = false;
	char insideBrackets[MAX_WORD_LENGTH] = {};
	int idxInsideBrackets = 0;
	char ch;

	while (inFile.get(ch))
	{
		if (ch == OPENING_BRACKET && (!isInsideOpeningBracket))
		{
			isInsideOpeningBracket = true;
		}
		else if (ch == CLOSING_BRACKET && isInsideOpeningBracket)
		{
			char* value = getValue(insideBrackets, dic);

			if (value != nullptr)
			{
				copy << value;
			}
			else
			{
				copy << OPENING_BRACKET << insideBrackets << CLOSING_BRACKET;
			}

			isInsideOpeningBracket = false;
			resetString(insideBrackets, '\0');
			idxInsideBrackets = 0;
		}
		else if (isInsideOpeningBracket)
		{
			if (idxInsideBrackets >= MAX_WORD_LENGTH - 1)
			{
				copy.close();
				return false;
			}

			insideBrackets[idxInsideBrackets] = ch;
			idxInsideBrackets++;
			insideBrackets[idxInsideBrackets] = '\0';
		}
		else
		{
			copy << ch;
		}
	}
	copy.close();

	return true;
}

int main()
{
	ifstream kvpFile(KEY_VALUE_PAIRS_FILE);
	if (!kvpFile.is_open())
	{
		return -1;
	}

	Dictionary dic = readKeyValuePairs(kvpFile);
	kvpFile.close();

	ifstream inputText(TEXT_FILE);
	if (!inputText.is_open())
	{
		delete[] dic.pairs;
		return -1;
	}
	
	getText(dic, inputText, COPY_FILE);

	delete[] dic.pairs;
	inputText.close();

	return 0;
}
